#version 330 core

in vec3 ov_color;

out vec4 fragment_color;

void main()
{
	fragment_color=vec4(ov_color, 1);
}