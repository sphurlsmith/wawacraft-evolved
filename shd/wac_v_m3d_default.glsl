#version 330 core

layout (location=0) in vec3 vertex_position;
layout (location=1) in vec3 vertex_color;
layout (location=2) in vec2 vertex_texture;

out vec3 ov_color;
out vec2 ov_tex;

uniform mat4 mod;
uniform mat4 proj;

void main()
{
	gl_Position=vec4(vertex_position, 1)*mod*proj;

	ov_color=vertex_color;
	ov_tex=vertex_texture;
}