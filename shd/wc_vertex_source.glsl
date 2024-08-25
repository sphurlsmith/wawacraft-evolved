#version 330 core

layout (location=0) in vec3 vp;
layout (location=1) in vec3 vc;
layout (location=2) in vec2 vt;

out vec3 voc;
out vec2 vtx;

void main(){
     gl_Position=vec4(vp, 1);

     voc=vc;
     vtx=vt;
}