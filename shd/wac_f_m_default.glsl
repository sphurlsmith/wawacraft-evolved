#version 330 core

in vec3 ov_color;
in vec2 ov_tex;

out vec4 fragment_color;

uniform sampler2D tex;

void main()
{
	// for use of colors, add in fragment_color*=vec4(ov_color, 1);
	fragment_color=texture(tex, ov_tex);

	if(fragment_color.a<0.2){
		discard;
	}
}