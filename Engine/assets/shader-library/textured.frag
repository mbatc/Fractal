#version 460

layout(binding = 2, std140) uniform Material {
  vec4 diffuseColour0;
};

uniform sampler2D diffuseMap0;

in vec4 vsout_position0;
in vec4 vsout_colour0;
in vec2 vsout_texcoord0;
in vec3 vsout_normal0;

const vec3 lightDir = vec3(1, 2, 0.7);
const vec3 lightCol = vec3(1, 0.7, 0.8);
const float strength = 1;

struct Lighting
{
  vec3 diffuse;
  vec3 specular;
};

Lighting CalcLighting(vec3 colour, vec3 lDir, float strength, vec3 viewDir, vec3 fragNormal, float shininess)
{
  Lighting l;
  l.diffuse = dot(lDir, fragNormal) * colour * strength;
  vec3 halfway = normalize(viewDir + lDir);
  l.specular = pow(max(dot(fragNormal, halfway), 0), shininess) * colour * strength;
  return l;
}

layout(binding = 0, std140) uniform Camera
{
  mat4 camMat;
  mat4 viewMat;
  mat4 projMat;
};

out vec4 fsout_colour0;

void main()
{
  vec3 camPos = (camMat * vec4(0,0,0,1)).xyz;
  vec3 fragPos = vsout_position0.xyz;
  vec3 viewDir = normalize(camPos - fragPos);

  Lighting lighting = CalcLighting(lightCol, normalize(lightDir), strength, viewDir, normalize(vsout_normal0), 32);

  fsout_colour0 = texture(diffuseMap0, vec2(vsout_texcoord0.x, 1 - vsout_texcoord0.y)) * vsout_colour0 * diffuseColour0;
  fsout_colour0.xyz *= lighting.diffuse;
  fsout_colour0.xyz += lighting.specular;
  fsout_colour0.a = 1;
}
