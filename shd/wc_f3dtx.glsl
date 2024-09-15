#version 330 core

out vec4 fc;

in vec3 voc;
in vec2 vtx;
in float p;

uniform sampler2D tex;

void main(){

     vec2 vta=vtx*p;

     fc=texture(tex, vta)*vec4(voc, 1);

     if(fc.a<0.2){
	discard;
     }

     if(voc==vec3(0,0,0)){
	fc=texture(tex, vtx);
     }
}
