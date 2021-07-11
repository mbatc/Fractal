#version 460

layout(location = 0) in vec3 position0;
layout(location = 1) in vec3 normal0;
layout(location = 2) in vec2 texcoord0;
layout(location = 3) in vec4 colour0;

out vec4 vsout_position0;
out vec4 vsout_colour0;
out vec2 vsout_texcoord0;
out vec3 vsout_normal0;
out vec3 vsout_cameraPosition0;

layout(binding = 0, std140) uniform Camera
{
  mat4 camMat;
  mat4 viewMat;
  mat4 projMat;
};

layout(binding = 1, std140) uniform Model
{
  mat4 modelMat;
  mat4 normalMat;
  mat4 mvp;
};

void main()
{
  vsout_position0 = modelMat * vec4(position0, 1);
  vsout_colour0   = colour0;
  vsout_texcoord0 = texcoord0;
  vsout_normal0   = normalize((normalMat * vec4(normal0, 1)).xyz);
  vsout_cameraPosition0 = (camMat * vec4(0,0,0,1)).xyz;

  gl_Position = mvp * vec4(position0, 1);
}
