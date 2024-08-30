#ifndef WINDOWDEF_H
#define WINDOWDEF_H

#include "libs.h"

// windowdef.h is a header file that provides the namespace nswcwin and the class wc_Window.
// these are used to define and manage windows.

// used to store any external utilities that are both for the use of the wc_Window methods and
// for any user planning to mod the game
namespace nswcwin{
  // resolution struct
  struct wc_res{
    int x; // width
    int y; // height
  };
}

// the main class of this header. wc_Window is used to create a graphical window with GLFW and
// GLAD, with most of its features being self-encapsulated.
class wc_Window{
 public:
  // the constructor sets up a window with a resolution, name, and
  // a render function callback in the form of a void function pointer
  wc_Window(nswcwin::wc_res res, std::string n, void (*p)());
  // calls wc_Window::endGLFW(); to turn the GLFWRunning flag off
  ~wc_Window();

  // utility function to set up a GLFW context. note that this also sets the GLFWRunning flag
  // true such that anybody can check if a GLFW context is open or not. good to note as well that
  // GLFW already has a function to do this but i figured if i did it myself it works well enough.
  static void startGLFW();
  // closes the GLFW context and sets the GLFWRunning flag off.
  static void endGLFW();

  // frontend function for initializing GLAD
  static void startGLAD();

  // sets the current GLFW context to a given window. this could be useful if you are planning to
  // manage multiple different windows at once!
  static void setCurrentWindow(GLFWwindow* p);
  // just resizes a given window given a resolution
  static void resizeWindow(GLFWwindow* p, nswcwin::wc_res res);

  // setup function for the window, independent of setting up the rendering frame within the window
  void setupWindow(nswcwin::wc_res window_resolution, std::string n);
  // instance-specific sister function of setCurrentWindow. cleverly named too :3
  void setThisCurrentWindow();

  // framebuffer resize callback function for when the user resizes a window. given a child class, we
  // could make this a virtual function and have a child class, say wc_PopUp refuse to integrate this
  // into its constructor function.
  void setFramebufferResizeCallback();
  // sets the render callback, which is fancy terms for a void function that runs all your openGL
  // rendering during the game loop
  void setRenderCallback(void (*p)());
  // the name says it all
  void runWindowLoopInstance();
  
  GLFWwindow* getWinPointer(); // get window handle

  void (*getRenderCallback())(); // get render callback

  static bool GLFWRunning; // utility bool. check to avoid starting GLFW twice
  
 private:

  void setViewport(int x, int y); // encapsulation since the viewport must be set following the setup of both GLFW *and* GLAD
  
  GLFWwindow* window_pointer; // Window handle.

  void (*renderf)(); // function pointer for rendering
};

#endif
