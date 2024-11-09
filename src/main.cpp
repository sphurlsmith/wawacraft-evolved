#include "libs.h"
#include "windowdef.h"
#include "shader.h"
#include "projection.h"
#include "textures.h"
#include "mesh.h"
#include "object.h"
#include "control.h"

// the render function
void rend(){
  glClearColor(.5, .5, .8, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(){
  std::vector<float> vert=
    {
      -1, -1, -1, 0, 0, 0, 0, 1,
      1,  -1, -1, 0, 0, 0, 1, 1,
      1,   1, -1, 0, 0, 0, 1, 0,
      -1,  1, -1, 0, 0, 0, 0, 0,
      -1, -1,  1, 0, 0, 0, 0, 1,
      1,  -1,  1, 0, 0, 0, 1, 1,
      1,   1,  1, 0, 0, 0, 1, 0,
      -1,  1,  1, 0, 0, 0, 0, 0,
      1,  -1, -1, 0, 0, 0, 0, 1,
      1,  -1,  1, 0, 0, 0, 1, 1,
      1,   1,  1, 0, 0, 0, 1, 0,
      1,   1, -1, 0, 0, 0, 0, 0,
      -1,  1, -1, 0, 0, 0, 0, 1,
      1,   1, -1, 0, 0, 0, 1, 1,
      1,   1,  1, 0, 0, 0, 1, 0,
      -1,  1,  1, 0, 0, 0, 0, 0,
      -1,  1,  1, 0, 0, 0, 0, 0,
      -1, -1,  1, 0, 0, 0, 0, 1,
      -1,  1, -1, 0, 0, 0, 1, 0,
      -1, -1, -1, 0, 0, 0, 1, 1,
      -1, -1, -1, 0, 0, 0, 0, 1,
      1,  -1, -1, 0, 0, 0, 1, 1,
      1,  -1,  1, 0, 0, 0, 1, 0,
      -1, -1,  1, 0, 0, 0, 0, 0,
    };

  std::vector<unsigned int> ind={
    0,   1,  2,  0,  2,  3,
    4,   5,  6,  4,  6,  7,
    8,   9, 10,  8, 10, 11,
    12, 13, 14, 12, 14, 15,
    17, 19, 18, 17, 18, 16,
    20, 21, 22, 20, 22, 23,
  };
  
  // getting the render function pointer
  void (*rpointer)()=&rend;
  
  // starting the game window 
  nswcwin::wc_res WINRES={800, 600};

  wc_Window WIN(WINRES, "Wawacraft Evolved [Alpha 0.0.0/October 31st Release] [OpenGL 3.3]", rpointer);

  wc_Shader def("shd/wc_vertex_3d.glsl", "shd/wc_fragment_source.glsl");
  wc_Texture wtx(32, 32, "tex/wawa.png");
  wc_BasicMesh wms(vert, ind);

  wc_Camera cam(WINRES.x, WINRES.y, 50*nsproj::DEGTORAD, .2, 10000, {0, 0, 0}, {0, 0, 1});
  wc_Object wawa(NULL, 1, {0, 0, 5}, {20*nsproj::DEGTORAD, 0, 0}, wms);

  def.activate();
  while(!glfwWindowShouldClose(WIN.getWinPointer())){
    glClearColor(.5, .5, .8, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    wtx.useTexture();
    cam.renderObject(&wawa, &def);

    nsproj::vec3 olr=wawa.getRotation();
    nsproj::vec3 nr={olr.x+nsproj::DEGTORAD, olr.y+nsproj::DEGTORAD, olr.z+nsproj::DEGTORAD};

    wawa.setRot(nr);
    
    if(nswincon::getKeyStatus(WIN.getWinPointer(), GLFW_KEY_W)==GLFW_PRESS){
      cam.moveFront(.2);
    }

    if(nswincon::getKeyStatus(WIN.getWinPointer(), GLFW_KEY_S)==GLFW_PRESS){
      cam.moveBack(.2);
    }

    if(nswincon::getKeyStatus(WIN.getWinPointer(), GLFW_KEY_A)==GLFW_PRESS){
      cam.strafeLeft(.2);
    }

    if(nswincon::getKeyStatus(WIN.getWinPointer(), GLFW_KEY_D)==GLFW_PRESS){
      cam.strafeRight(.2);
    }

    if(nswincon::getKeyStatus(WIN.getWinPointer(), GLFW_KEY_PAGE_UP)==GLFW_PRESS){
      cam.setPosition({cam.getPosition().x, cam.getPosition().y+.2, cam.getPosition().z});
    }

    if(nswincon::getKeyStatus(WIN.getWinPointer(), GLFW_KEY_PAGE_DOWN)==GLFW_PRESS){
      cam.setPosition({cam.getPosition().x, cam.getPosition().y-.2, cam.getPosition().z});
    }

    if(nswincon::getKeyStatus(WIN.getWinPointer(), GLFW_KEY_LEFT)==GLFW_PRESS){
      cam.setAngleHorizontal(cam.getAngleHorizontal()-5*nsproj::DEGTORAD);
    }

    if(nswincon::getKeyStatus(WIN.getWinPointer(), GLFW_KEY_RIGHT)==GLFW_PRESS){
      cam.setAngleHorizontal(cam.getAngleHorizontal()+5*nsproj::DEGTORAD);
    }

    if(nswincon::getKeyStatus(WIN.getWinPointer(), GLFW_KEY_UP)==GLFW_PRESS){
      cam.setAngleVertical(cam.getAngleVertical()+5*nsproj::DEGTORAD);
    }

    if(nswincon::getKeyStatus(WIN.getWinPointer(), GLFW_KEY_DOWN)==GLFW_PRESS){
      cam.setAngleVertical(cam.getAngleVertical()-5*nsproj::DEGTORAD);
    }

    glfwSwapBuffers(glfwGetCurrentContext());
    glfwPollEvents();
  }
  
  return 0;
}
