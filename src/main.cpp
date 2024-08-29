#include "libs.h"
#include "windowdef.h"
#include "shader.h"
#include "textures.h"
#include "mesh.h"

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

  wc_Texture shatex(32, 32, "tex/wawa.png");
  wc_BasicMesh shawa(vert, ind);

  shatex.useTexture();
  shawa.renderMesh();
}

int main(){
  // getting the render function pointer
  void (*rpointer)()=&rend;
  
  // starting the game window 
  nswcwin::wc_res WINRES={800, 600};

  wc_Window WIN(WINRES, "Wawacraft Evolved [OpenGL 3.3]", rpointer);
  shader def("shd/wc_vertex_source.glsl", "shd/wc_fragment_source.glsl");
  
  def.activate();
  while(!glfwWindowShouldClose(WIN.getWinPointer())){
    WIN.runWindowLoopInstance();
  }
  
  return 0;
}
