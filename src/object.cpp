#include "libs.h"
#include "shader.h"
#include "projection.h"
#include "mesh.h"
#include "object.h"

// this is the implementation of the object.h header, a header that
// creates for us simple classes that allow for the rendering and
// managing of a 3d scene.

wc_Object::wc_Object(void (*rc)(), float s, nsproj::vec3 p, nsproj::vec3 r, wc_BasicMesh m):
  rend_c(rc),
  size(s),
  position(p),
  rotation(r),
  mesh(m){
  constructModelMatrix();
}

void wc_Object::constructModelMatrix(){
  model=nsproj::modelMatrix(rotation, position, size);
}

void wc_Object::render(){
  try{
    if(rend_c==NULL){
      throw "invalid-wc-object-rendercallback";
    }else{
      (*rend_c)();
    }
  }catch(const char* err){
    std::cout << "Exception approached: " << err << std::endl;
  }

  mesh.renderMesh();
}

void wc_Object::setRenderCallback(void (*r)()){
  rend_c=r;
}

void wc_Object::setSize(float s){
  size=s;
}

void wc_Object::setPos(nsproj::vec3 pos){
  position=pos;
}

void wc_Object::setRot(nsproj::vec3 rot){
  rotation=rot;
}

void wc_Object::setMesh(wc_BasicMesh m){
  mesh=m;
}

void (*wc_Object::getRenderCallback())(){
  return rend_c;
}

float wc_Object::getSize(){
  return size;
}

nsproj::vec3 wc_Object::getPosition(){
  return position;
}

nsproj::vec3 wc_Object::getRotation(){
  return rotation;
}

nsproj::mat4& wc_Object::getModelMatrix(){
  return model;
}

wc_BasicMesh wc_Object::getMesh(){
  return mesh;
}

wc_Camera::wc_Camera(float px, float py, float fv, float n, float f, nsproj::vec3 pos, nsproj::vec3 tar):
  ax(px),
  ay(py),
  fov(fv),
  near_p(n),
  far_p(f),
  position(pos),
  target(tar){
  up={0,1,0};
  
  constructViewMatrix();
  constructProjectionMatrix();
}

void wc_Camera::constructViewMatrix(){
  nsproj::vec3 tr=target;

  float cva=cos(va/2);
  float sva=sin(va/2);

  float cha=cos(-ha/2);
  float sha=sin(-ha/2);
  
  quat va(cva, sva, 0, 0);
  quat ha(cha, 0, sha, 0);

  va=va.normal();
  ha=ha.normal();

  quat q(1,1,1,1);
  q=quat::product(ha, va);

  quat t(0, tr.x, tr.y, tr.z);
  t=quat::conjugation(t, ha);
  tr={t.i, t.j, t.k};
  
  view=nsproj::viewMatrix(up, tr, position);
  nsproj::debugOutputMatrix(view);
}

void wc_Camera::constructProjectionMatrix(){
  projection=nsproj::perspectiveProjectionMatrix(fov, ay/ax, near_p, far_p);
}

void wc_Camera::renderObject(wc_Object* o, wc_Shader* sh){
  constructViewMatrix();
  sh->activate();
  
  sh->setUniformMatrix("mod",  true, &(o->getModelMatrix().m[0][0]));
  sh->setUniformMatrix("view", false, &view.m[0][0]);
  sh->setUniformMatrix("proj", true, &projection.m[0][0]);

  nsproj::mat4 tot=(o->getModelMatrix())*(view)*(projection);
  nsproj::vec4 p={.5, .5, 3, 1};
  p*=tot;
  nsproj::vec3 n=normalizeVec4(p);
  
  o->render();
}

void wc_Camera::setAspectRatio(float x, float y){
  ax=x;
  ay=y;
}

void wc_Camera::setAngleHorizontal(float a){
  ha=a;
  if(ha>360*nsproj::DEGTORAD){ha-=360*nsproj::DEGTORAD;}
  if(ha<0){ha+=360*nsproj::DEGTORAD;}
}

void wc_Camera::setAngleVertical(float a){
  va=a;
  if(va>90*nsproj::DEGTORAD){va=90*nsproj::DEGTORAD;}
  if(va<-90*nsproj::DEGTORAD){va=-90*nsproj::DEGTORAD;}
}

void wc_Camera::setFOV(float f){
  fov=f;
}

void wc_Camera::setPlanes(float n, float f){
  near_p=n;
  far_p=f;
}

void wc_Camera::setPosition(nsproj::vec3 pos){
  position=pos;
}

void wc_Camera::setTarget(nsproj::vec3 tar){
  target=tar;
}

void wc_Camera::moveFront(float sp){
  nsproj::vec3 ttran={0,0,1};

  ttran=nsproj::rotateVec3Quat(ttran, {0,1,0}, ha);
  ttran=nsproj::rotateVec3Quat(ttran, {1,0,0}, va);
  ttran=nsproj::scaleVec3(ttran, sp);
  
  position=nsproj::translateVec3(position, ttran);
}

void wc_Camera::moveBack(float sp){
  nsproj::vec3 ttran={0,0,1};

  ttran=nsproj::rotateVec3Quat(ttran, {0,1,0}, ha);
  ttran=nsproj::rotateVec3Quat(ttran, {1,0,0}, va);
  ttran=nsproj::scaleVec3(ttran, sp);

  position=nsproj::subtractVec3(position, ttran);
}

void wc_Camera::strafeRight(float sp){
  nsproj::vec3 ttran={0,0,1};
  nsproj::vec3 up={0,1,0};
  
  ttran=nsproj::rotateVec3Quat(ttran, {0,1,0}, ha);
  ttran=nsproj::rotateVec3Quat(ttran, {1,0,0}, va);
  ttran=nsproj::scaleVec3(ttran, sp);

  nsproj::vec3 right=nsproj::cross(up, ttran);
  
  position=nsproj::translateVec3(position, right);
}

void wc_Camera::strafeLeft(float sp){
  nsproj::vec3 ttran={0,0,1};
  nsproj::vec3 up={0,1,0};
  
  ttran=nsproj::rotateVec3Quat(ttran, {0,1,0}, ha);
  ttran=nsproj::rotateVec3Quat(ttran, {1,0,0}, va);
  ttran=nsproj::scaleVec3(ttran, sp);

  nsproj::vec3 left=nsproj::cross(ttran, up);

  position=nsproj::translateVec3(position, left);
}

float wc_Camera::getAspectX(){
  return ax;
}

float wc_Camera::getAspectY(){
  return ay;
}

float wc_Camera::getAngleHorizontal(){
  return ha;
}

float wc_Camera::getAngleVertical(){
  return va;
}

float wc_Camera::getFOV(){
  return fov;
}

float wc_Camera::getNearPlane(){
  return near_p;
}

float wc_Camera::getFarPlane(){
  return far_p;
}

nsproj::vec3 wc_Camera::getPosition(){
  return position;
}

nsproj::vec3 wc_Camera::getTarget(){
  return target;
}

nsproj::mat4& wc_Camera::getViewMatrix(){
  return view;
}

nsproj::mat4& wc_Camera::getProjectionMatrix(){
  return projection;
}
