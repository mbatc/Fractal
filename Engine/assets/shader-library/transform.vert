#version 330

layout(location = 0) in vec3 position0;
layout(location = 1) in vec3 normal0;
layout(location = 2) in vec4 colour0;

out vec3 vsout_position0;
out vec4 vsout_colour0;

uniform mat4 mvp;

void main()
{
  vsout_position0 = position0;
  vsout_colour0 = colour0;
  gl_Position = mvp * vec4(position0, 1);
}
