#version 330

in vec3 position0;
in vec3 normal0;
in vec4 colour0;
in vec2 texcoord0;

out vec3 vsout_position0;
out vec4 vsout_colour0;
out vec2 vsout_texcoord0;

uniform mat4 mvp;

void main()
{
  vsout_position0 = position0;
  vsout_colour0 = colour0;
  vsout_texcoord0 = texcoord0;
  gl_Position = mvp * vec4(position0, 1);
}