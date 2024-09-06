#ifndef OBJECT_H
#define OBJECT_H

#include "libs.h"
#include "projection.h"
#include "mesh.h"

// this is the object.h header used in order to supply the game with the classes
// necessary to create the contextual objects of a camera and objects to supply
// a scene. The camera keeps the rotation, and position of every object in accordance
// with it, as well as its own editable projection matrix.

// class used to create a world object with attributes, a mesh, and a render callback.
// requires a mesh, a position, rotation, and size attribute in order to construct
// the model matrix for the object.
class wc_Object{
 public:
  wc_Object(void (*r)(), float s, nsproj::vec3 p, nsproj::vec3 r, wc_BasicMesh m);

  void constructModelMatrix();
  void render();
  
  void setRenderCallback(void (*r)());
  void setSize(float s);

  void setPos(nsproj::vec3 pos);
  void setRot(nsproj::vec3 rot);

  void setMesh(wc_BasicMesh m);
  
  void (*getRenderCallback)();
  float getSize();

  nsproj::vec3 getPosition();
  nsproj::vec3 getRotation();

  nsproj::mat4& getModelMatrix();

  wc_BasicMesh getMesh();
 private:

  void (*rend_c)(); 
  
  float size;
  
  nsproj::vec3 position;
  nsproj::vec3 rotation;

  nsproj::mat4 model;
  
  wc_BasicMesh mesh;
};

// this class is to define a proper camera, that can then interpret wc_Object classes,
// and render them in full 3d, by supplying the remaining view and projection matrices
// to the shader, and rendering the object. There are possibilities of creating a
// render queue and having the wc_Camera cycle through via pointer, which would be
// quite epic I think :3
class wc_Camera{
 public:
  wc_Camera(float px, float py, float fv, float n, float f, nsproj::vec3 pos, nsproj::vec3 rot);
  
  void constructViewMatrix();
  void constructProjectionMatrix();

  void renderObject(wc_Object o);
  
  void setAspectRatio(float x, float y);

  void setFOV(float f);
  void setPlanes(float n, float f);

  void setPosition(nsproj::vec3 pos);
  void setRotation(nsproj::vec3 rot);

  float getAspectX();
  float getAspectY();

  float getFOV();
  float getNearPlane();
  float getFarPlane();

  nsproj::vec3 getPosition();
  nsproj::vec3 getRotation();

  nsproj::mat4& getViewMatrix();
  nsproj::mat4& getProjectionMatrix();
  
 private:
  float ax;
  float ay;
  
  float fov;
  float near_p;
  float far_p;
  
  nsproj::vec3 position;
  nsproj::vec3 rotation;

  nsproj::mat4 view;
  nsproj::mat4 projection;
};

#endif
