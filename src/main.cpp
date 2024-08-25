#include "libs.h"
#include "windowdef.h"
#include "shader.h"

// the render function
void rend(){
  glClearColor(.5, .5, .8, 1);

  glClear(GL_COLOR_BUFFER_BIT);
}

int main(){
  // getting the render function pointer
  void (*rpointer)()=&rend;
  
  // starting the game window 
  nswcwin::wc_res WINRES={800, 600};

  wc_Window WIN(WINRES, "Wawacraft Evolved [OpenGL 3.3]", rpointer);
  shader def("shaders/wc_vertex_source.glsl", "shaders/wc_fragment_source.glsl");

  def.activate();
  while(!glfwWindowShouldClose(WIN.getWinPointer())){
    WIN.runWindowLoopInstance();
  }
  
  return 0;
}
