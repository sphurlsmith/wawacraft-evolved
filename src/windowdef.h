#ifndef WINDOWDEF_H
#define WINDOWDEF_H

#include "libs.h"

namespace nswcwin{
  // resolution struct
  struct wc_res{
    int x;
    int y;
  };
}

class wc_Window{
 public:
  wc_Window(nswcwin::wc_res res, std::string n, void (*p)());
  ~wc_Window();

  static void startGLFW(); // self explanatory
  static void endGLFW();

  static void startGLAD();
  
  static void setCurrentWindow(GLFWwindow* p);
  static void resizeWindow(GLFWwindow* p, int x, int y);
  
  void setupWindow(nswcwin::wc_res window_resolution, std::string n);
  void setThisCurrentWindow();

  void setFramebufferResizeCallback();
  void setRenderCallback(void (*p)());
  void runWindowLoopInstance();
  
  GLFWwindow* getWinPointer(); // get window handle

  void (*getRenderCallback())(); // get render callback

  static bool GLFWRunning; // check to avoid starting GLFW twice
  
 private:

  void setViewport(int x, int y); // encapsulation since the viewport must be set following the setup of both GLFW *and* GLAD
  
  GLFWwindow* window_pointer; // Window handle.

  void (*renderf)(); // function pointer for rendering
};

#endif
