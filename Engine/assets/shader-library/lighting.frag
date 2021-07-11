#version 460

const int directionalLight = 0
const int spotLight  = 1;
const int pointLight = 2;

in vec3 vsout_position0;
in vec4 vsout_colour0;
in vec2 vsout_texcoord0;
in vec2 vsout_normal0;

struct Light
{
  vec3 colour;
  int type;
  vec3 position;
  float strength;
  vec3 direction;
  float cutoff;
  float falloff;
};

layout(binding = 2, std140) buffer LightBuffer
{
  Light[] lights;
};

layout(binding = 0, std140) uniform Camera
{
  mat4 camMat;
  mat4 viewMat;
  mat4 projMat;
};

struct Lighting
{
  vec3 diffuse;
  vec3 specular;
};

vec2 CalcDirectionalLight(vec3 colour, vec3 lightDirection, float strength, vec3 viewDirection, vec3 normal, float shininess)
{
  Lighting l;
  l.diffuse = dot(lightDirection, normal) * colour * strength;
  vec3 halfway = normalize(viewDirection + lightDirection);
  l.specular = pow(max(dot(normal, halfway), 0), shininess) * colour * strength;

  return l;
}

void main()
{
  Lighting accumLighting;
  for (int i = 0; i < lights.length(); ++i)
  {
    Lighting l;
    switch (lights[i].type)
    {
    case directionalLight:
      l = CalcDirectionalLight(
        lights[i].colour,
        lights[i].direction,
        lights[i].strength,

      );

      break;
    case spotLight:
      l = CalcSpotLight();
      break;
    case pointLight:
      l = CalcPointLight();
      break;
    }

    accumLighting.diffuse += l.diffuse;
    accumLighting.specular += l.specular;
  }

  fsout_colour0 = texture(diffuseMap0, vec2(vsout_texcoord0.x, 1 - vsout_texcoord0.y)) * vsout_colour0 * diffuseColour0;
  fsout_colour0.xyz *= accumLighting.diffuse;
  fsout_colour0.xyz += accumLighting.specular;
  fsout_colour0.a = 1;
}