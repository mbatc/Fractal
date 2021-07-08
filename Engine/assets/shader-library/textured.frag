#version 330

in vec2 vsout_texcoord0;
in vec4 vsout_colour0;

uniform Material {
  vec4 diffuseColour0;
};

uniform sampler2D diffuseMap0;

out vec4 fsout_colour0;

void main()
{
  fsout_colour0 = texture(diffuseMap0, vec2(vsout_texcoord0.x, 1 - vsout_texcoord0.y)) * vsout_colour0 * diffuseColour0;
  fsout_colour0.a = 1;
}
