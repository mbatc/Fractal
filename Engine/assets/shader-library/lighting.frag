#version 460

// Structures and constants
struct Light
{
  vec3 colour;       // 0-12
  int type;          // 12-16

  vec3 ambient;      // 16-28
  float strength;    // 28-32

  vec3 position;     // 32-44
  float falloff;     // 44-48

  vec3 direction;    // 48-60
  float innerCutoff; // 60-64

  float outerCutoff; // 64-68

  // Padding struct to vec4 alignment
  float padding0;
  float padding1;
  float padding2;
};

struct Lighting
{
  vec3 diffuse;
  vec3 specular;
  vec3 ambient;
};

const int directionalLight = 0;
const int pointLight = 1;
const int spotLight  = 2;

const float screenGamma = 2.2;

// Shader inputs
in vec4 vsout_position0;
in vec4 vsout_colour0;
in vec2 vsout_texcoord0;
in vec3 vsout_normal0;
in vec3 vsout_cameraPosition0;

// Material Input
layout(binding = 2, std140) uniform Material {
  vec4 diffuseColour0;
  float specularPower0;
};

uniform sampler2D diffuseMap0;

// Scene Inputs
layout(binding = 3, std140) buffer LightBuffer
{
  Light[] lights;
};

Lighting CalcDirectionalLight(vec3 colour, vec3 lightDirection, float strength, vec3 viewDirection, vec3 normal, float shininess)
{
  Lighting l;
  float lambertian = max(dot(lightDirection, normal), 0.0);
  l.diffuse = lambertian * colour * strength;
  vec3 halfway = normalize(viewDirection + lightDirection);
  float specularAmount = mix(0, pow(max(dot(normal, halfway), 0), shininess), int(lambertian > 0));
  l.specular = specularAmount * colour * strength;
  return l;
}

Lighting CalcPointLight(vec3 colour, vec3 lightPosition, float falloff, float strength, vec3 viewDirection, vec3 fragPos, vec3 normal, float shininess)
{
  vec3 lightDirection = lightPosition - fragPos;
  float dist = length(lightDirection);
  lightDirection /= dist;
  Lighting l = CalcDirectionalLight(colour, lightDirection, strength, viewDirection, normal, shininess);
  float factor = (1 - clamp(pow(dist / strength, falloff), 0, 1));
  l.specular *= factor;
  l.diffuse  *= factor;
  return l;
}

Lighting CalcSpotLight(vec3 colour, vec3 lightPosition, vec3 lightDirection, float falloff, float innerCutoff, float outerCutoff, float strength, vec3 viewDirection, vec3 fragPos, vec3 normal, float shininess)
{
  vec3 lightToFrag =  lightPosition - fragPos;
  float dist = length(lightToFrag);
  lightToFrag /= dist;

  Lighting l = CalcDirectionalLight(colour, lightToFrag, strength, viewDirection, normal, shininess);
  float factor = (1 - clamp(pow(dist / strength, falloff), 0, 1));

  float theta     = dot(lightToFrag, lightDirection);
  float epsilon   = innerCutoff - outerCutoff;
  float intensity = clamp((theta - outerCutoff) / epsilon, 0.0, 1.0);   

  l.specular *= factor * intensity;
  l.diffuse  *= factor * intensity;
  return l;
}

out vec4 fsout_colour0;

void main()
{
  vec3 fragPos    = vsout_position0.xyz;
  vec3 fragNormal = normalize(vsout_normal0);
  vec3 viewDir    = normalize(vsout_cameraPosition0 - fragPos);

  fsout_colour0 = vec4(1, 0, 0, 1);

  Lighting accumLighting;
  accumLighting.diffuse  = vec3(0);
  accumLighting.specular = vec3(0);
  accumLighting.ambient = vec3(0);

  if (lights.length() > 0)
  {
    for (int i = 0; i < lights.length(); ++i)
    {
      Lighting l;
      switch (lights[i].type)
      {
      case directionalLight:
        l = CalcDirectionalLight(
          lights[i].colour,
          normalize(lights[i].direction),
          lights[i].strength,
          viewDir,
          fragNormal,
          256
        );

        l.ambient = lights[i].ambient;

        break;
      case pointLight:
        l = CalcPointLight(
          lights[i].colour,
          lights[i].position,
          lights[i].falloff,
          lights[i].strength,
          viewDir,
          fragPos,
          fragNormal,
          256
        );
        break;

      case spotLight:
        l = CalcSpotLight(
          lights[i].colour,
          lights[i].position,
          normalize(lights[i].direction),
          lights[i].falloff,
          lights[i].innerCutoff,
          lights[i].outerCutoff,
          lights[i].strength,
          viewDir,
          fragPos,
          fragNormal,
          256
        );
        break;
      }

      accumLighting.diffuse  += l.diffuse;
      accumLighting.specular += l.specular;
      accumLighting.ambient  += l.ambient;
    }
  }
  else
  {
    accumLighting.diffuse  = vec3(1);
    accumLighting.specular = vec3(0);
    accumLighting.ambient  = vec3(0);
  }

  fsout_colour0 = texture(diffuseMap0, vec2(vsout_texcoord0.x, 1 - vsout_texcoord0.y)) * vsout_colour0 * diffuseColour0;
  fsout_colour0.xyz *= (accumLighting.ambient + accumLighting.diffuse);
  fsout_colour0.xyz += accumLighting.specular;
  fsout_colour0.a = 1;
}
