#version 330 core

layout (location=0) in vec3 vp;
layout (location=1) in vec3 vc;
layout (location=2) in vec2 vt;

out vec3 voc;
out vec2 vtx;

uniform mat4 mod;
uniform mat4 view;
uniform mat4 proj;

void main(){
     gl_Position=vec4(vp, 1)*mod*view*proj;

     voc=vc;
     vtx=vt;
}