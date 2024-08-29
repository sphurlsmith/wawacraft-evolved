#include "libs.h"
#include "windowdef.h"

// initializing the GLFW run flag
static bool wc_Window::GLFWRunning=false;

wc_Window::wc_Window(nswcwin::wc_res res, std::string n, void (*p)()){
  if(!GLFWRunning){
    startGLFW();
  }

  setupWindow(res, n);
  setCurrentWindow(window_pointer);
  startGLAD();

  setViewport(res.x, res.y);
  
  setRenderCallback(p);
  setFramebufferResizeCallback();
}

wc_Window::~wc_Window(){
  endGLFW();
}

// function to set up GLFW. Static for convenience.
static void wc_Window::startGLFW(){
  // starting the GLFW contexts
  glfwInit();

  // window hints and requirements for a GLFW context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //glEnable(GL_DEBUG_OUTPUT); // me when no FUCKING DEBUG OUTPUT UNTIL 4.6 FUCK THIS DSHIT

  GLFWRunning=true;
}

// self explanatory
static void wc_Window::endGLFW(){
  glfwTerminate();
  GLFWRunning=false;
}

static void wc_Window::startGLAD(){
  try{

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){throw "failed-glad";}
  }catch(const char* err){
    std::cout << "Exception approached: " << err << std::endl;
  }
}

static void wc_Window::setCurrentWindow(GLFWwindow* p){
  glfwMakeContextCurrent(p);
}

static void wc_Window::resizeWindow(GLFWwindow* p, int x, int y){
  glViewport(0, 0, x, y);
}

void wc_Window::setupWindow(nswcwin::wc_res window_resolution, std::string n){
  try{
    window_pointer=glfwCreateWindow(window_resolution.x, window_resolution.y, n.c_str(), NULL, NULL);

    if(window_pointer==NULL){throw "failed-wincreation";}
  }catch(const char* err){
    std::cout << "Exception approached: " << err << std::endl;
  }
}

void wc_Window::setThisCurrentWindow(){
  glfwMakeContextCurrent(this->window_pointer);
}

void wc_Window::setFramebufferResizeCallback(){
  glfwSetFramebufferSizeCallback(window_pointer, wc_Window::resizeWindow);
}

void wc_Window::setRenderCallback(void (*p)()){
  try{
    this->renderf=p;

    if(renderf==NULL){
      throw "invalid-wc-win-rendercallback";
    }
  }catch(const char* err){
    std::cout << "Exception approached: " << err << std::endl;
  }
}

void wc_Window::runWindowLoopInstance(){
  setThisCurrentWindow();

  try{
    if(renderf==NULL){
      throw "invalid-wc-win-rendercallback";
    }
    
    (*renderf)(); // verify that the function pointer is valid first.
  }catch(const char* err){
    std::cout << "Exception approached: " << err << std::endl;
  }

  glfwSwapBuffers(glfwGetCurrentContext());
  glfwPollEvents(); // only works when our window object is the current GLFW context.
}

GLFWwindow* wc_Window::getWinPointer(){
  return window_pointer;
}

void (*wc_Window::getRenderCallback())(){
  return renderf;
}

void wc_Window::setViewport(int x, int y){
  glViewport(0, 0, x, y);
}
