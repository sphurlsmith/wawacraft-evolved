#include "libs.h"
#include "windowdef.h"
#include "shader.h"
#include "projection.h"
#include "textures.h"
#include "mesh.h"
#include "object.h"

// the render function
void rend(){
  glClearColor(.5, .5, .8, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  std::vector<float> vert=
    {
      -.5, -.5, 0, 1, 0, 0, 0, 1,
      .5,  -.5, 0, 0, 1, 0, 1, 1,
      .5,   .5, 0, 0, 0, 1, 1, 0,
      -.5,  .5, 0, 1, 1, 0, 0, 0
    };

  std::vector<unsigned int> ind={0, 1, 2, 0, 2, 3};

  wc_Shader def3d("shd/wc_vertex_3d.glsl", "shd/wc_fragment_source.glsl");
  
  wc_Texture shatex(32, 32, "tex/wawa.png");
  wc_BasicMesh shawa(vert, ind);
  
  shatex.useTexture();
  //shawa.renderMesh();

  wc_Object sha3d(NULL, 1, {0, 0, 3}, {20*nsproj::DEGTORAD, 20*nsproj::DEGTORAD, 0}, shawa);
  wc_Camera cam(800, 600, 50*nsproj::DEGTORAD, 1, 10, {0,0,0}, {0,0,0});

  def3d.activate();
  cam.renderObject(&sha3d, &def3d);
}

int main(){
  // getting the render function pointer
  void (*rpointer)()=&rend;
  
  // starting the game window 
  nswcwin::wc_res WINRES={800, 600};

  wc_Window WIN(WINRES, "Wawacraft Evolved [OpenGL 3.3]", rpointer);
  wc_Shader def("shd/wc_vertex_source.glsl", "shd/wc_fragment_source.glsl");
  
  while(!glfwWindowShouldClose(WIN.getWinPointer())){
    def.activate();
    WIN.runWindowLoopInstance();
  }
  
  return 0;
}
