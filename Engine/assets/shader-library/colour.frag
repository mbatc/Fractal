#version 330

in vec3 vsout_position0;
in vec4 vsout_colour0;

out vec4 fsout_colour0;

void main()
{
  fsout_colour0 = vsout_colour0;
}
