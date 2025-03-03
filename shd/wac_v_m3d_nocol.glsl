#version 330 core

layout (location=0) in vec3 vertex_position;
layout (location=2) in vec2 vertex_texture;
layout (location=3) in float vertex_shade;

out vec2 ov_tex;
out float ov_shade;

uniform mat4 mod;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position=vec4(vertex_position, 1)*mod*view*proj;

	ov_tex=vertex_texture;
	ov_shade=vertex_shade;
}