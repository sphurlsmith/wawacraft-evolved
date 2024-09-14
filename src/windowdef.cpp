#include "libs.h"
#include "windowdef.h"

// an implementation of the windowdef.h header.

// initializing the GLFW run flag since it is a static variable
static bool wc_Window::GLFWRunning=false;

// the constructor of wc_Window. requires a resolution, name, and function
// pointer to respectively set the render callback, window resolution, and
// window name
wc_Window::wc_Window(nswcwin::wc_res res, std::string n, void (*p)()){
  // clever trick of seeing if GLFW has already been set up
  // this is to account for multiple wc_Window instances
  // down the line
  if(!GLFWRunning){
    startGLFW();
  }

  setupWindow(res, n); // sets up a window in the OS with a resolution and name
  setThisCurrentWindow(); // binds the current operating window to itself
  startGLAD(); // registers a handle for the window with GLAD

  // creates a viewport to render within.
  setViewport(res.x, res.y);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  
  setRenderCallback(p); // sets the render callback for render loop
  setFramebufferResizeCallback(); // sets the framebuffer resize callback for resizing windows.
}

// calls endGLFW to say that the GLFW context has been terminated to future wc_Windows.
wc_Window::~wc_Window(){
  endGLFW();
}

// function to set up GLFW. Static for convenience.
static void wc_Window::startGLFW(){
  // starting the GLFW contexts
  glfwInit();

  // window hints and requirements for a GLFW context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // sets to OpenGL 3.3 Core profile.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // this context is the one with the most functionality and compatibility, so the game could run on old computers.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //glEnable(GL_DEBUG_OUTPUT); // me when no FUCKING DEBUG OUTPUT UNTIL 4.6 FUCK THIS DSHIT // yes that was quite the reaction to have :3

  GLFWRunning=true;
}

// self explanatory
static void wc_Window::endGLFW(){
  glfwTerminate();   // actually ends GLFW context
  GLFWRunning=false; // broadcasts that the GLFW context has ended
}

// begins a GLAD handle for the window
static void wc_Window::startGLAD(){
  // everything here is put in exception handling to make sure we arent dealing with missing drivers on runtime or such
  // well we will be its just that we will have warned the user about it beforehand :3
  try{

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){throw "failed-glad";}
  }catch(const char* err){
    std::cout << "Exception approached: " << err << std::endl;
  }
}

// sets the current GLFW context to a given GLFWWindow pointer. static for convenience
static void wc_Window::setCurrentWindow(GLFWwindow* p){
  glfwMakeContextCurrent(p);
}

// resizes a given GLFWWindow's render viewport. it is intended for regular use independent
// of openGL as it uses our nswcwin::wc_res struct instead of 2 ints. The OpenGL callback
// is found right under it
static void wc_Window::resizeWindow(GLFWwindow* p, nswcwin::wc_res res){
  glViewport(0, 0, res.x, res.y); // basically just restricts the render viewport
}

// this is the resize callback alternative that OpenGL will use in order to resize the window
// OpenGL was not built with structs in mind, which is sad really
static void wc_Window::resizeWindow(GLFWwindow* p, int x, int y){
  glViewport(0, 0, x, y);
}

// sets up an instance's real window with GLFW given a resolution wc_res, and a name in a string
void wc_Window::setupWindow(nswcwin::wc_res window_resolution, std::string n){
  try{
    window_pointer=glfwCreateWindow(window_resolution.x, window_resolution.y, n.c_str(), NULL, NULL);

    if(window_pointer==NULL){throw "failed-wincreation";} // some wizard fucked up the boot
  }catch(const char* err){
    std::cout << "Exception approached: " << err << std::endl;
  }
}

// instance-specific sister function of wc_Window::setCurrentWIndow(GLFWWindow*);
void wc_Window::setThisCurrentWindow(){
  glfwMakeContextCurrent(this->window_pointer);
}

// sets the framebuffer resize callback for the instance.
void wc_Window::setFramebufferResizeCallback(){
  glfwSetFramebufferSizeCallback(window_pointer, wc_Window::resizeWindow); // mmm i love referencing functions semantically
}

// setting the render callback of the window instance, requiring the parameter of a void function pointer
// with no parameters. in BASIC terms it just asks you to give it a subroutine to reference. Very Nice!
void wc_Window::setRenderCallback(void (*p)()){
  // there is always a big risk with pointers that somebody handled them wrong. Usually it happens because somebody kills an
  // object before they do its pointer, meaning that the pointer just leads to the graveyard, home of Undefined behaviour.
  // this is especially dangerous because if we even get close to running instructions from the graveyard, we are no longer
  // in control of our program. Usually the operating system recognises we are trying to access memory outside of our domain,
  // and gives us SEGMENTATION FAULT(CORE DUMPED) by throwing away everything and well, sending it to the graveyard.
  // Wise words of the day: never run instructions from the graveyard.
  try{
    if(p==NULL){
      throw "invalid-wc-win-rendercallback";
    }else{
      this->renderf=p; // good to note that even in its useless state, the render callback will not be set until after we verify the pointer
    }
  }catch(const char* err){
    std::cout << "Exception approached: " << err << std::endl;
  }
}

// runs an instance of the window render loop by running the render callback
// and swapping the buffers to reveal things. Note that this restricts the
// user to drawing things only within the render callback, which is OK ig.
void wc_Window::runWindowLoopInstance(){
  setThisCurrentWindow();

  try{
    if(renderf==NULL){
      throw "invalid-wc-win-rendercallback"; // some idiot tried to run instructions from the graveyard
    }
    
    (*renderf)(); // verify that the function pointer is valid first.
  }catch(const char* err){
    std::cout << "Exception approached: " << err << std::endl;
  }

  glfwSwapBuffers(glfwGetCurrentContext()); // swaps to the drawn buffer
  glfwPollEvents(); // only works when our window object is the current GLFW context.
}

// get the raw GLFW window handle from an instance
GLFWwindow* wc_Window::getWinPointer(){
  return window_pointer;
}

// getting the raw render callback from an instance
void (*wc_Window::getRenderCallback())(){
  return renderf;
}

// setting the viewport(render window) of OpenGL in a wc_Window instance. Very Nice!
void wc_Window::setViewport(int x, int y){
  glViewport(0, 0, x, y);
}
