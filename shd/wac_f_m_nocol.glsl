#version 330 core

in vec2 ov_tex;
in float ov_shade;

out vec4 fragment_color;

uniform sampler2D tex;

void main()
{
	vec4 shade=vec4(ov_shade, ov_shade, ov_shade, 1);
	fragment_color=shade*texture(tex, ov_tex);
	
	if(fragment_color.a<0.2){
		discard;
	}
}