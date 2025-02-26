#version 330 core

layout (location=0) in vec3 vertex_position;
layout (location=1) in vec3 vertex_color;

out vec3 ov_color;

void main()
{
	gl_Position=vec4(vertex_position, 1);

	ov_color=vertex_color;
}