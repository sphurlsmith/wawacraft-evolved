#version 330 core

layout (location=0) in vec3 vp;
layout (location=1) in vec3 vc;
layout (location=2) in vec2 vt;

out vec3 voc;
out vec2 vtx;
out float p;

uniform mat4 mod;
uniform mat4 view;
uniform mat4 proj;

void main(){
     gl_Position=vec4(vp, 1)*mod;
     gl_Position*=view;
     gl_Position*=proj;

     //gl_Position/=gl_Position.w;

     vtx=vt;
     p=1/1;

     voc=vc;
}