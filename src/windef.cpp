#include "libs.h"
#include "windef.h"

static bool window::glfw_initialized=false;

window::window(int pxres, int pyres, std::string pt):
  xres(pxres),
  yres(pyres),
  title(pt)
{
  // std::cout << "Initializing window " << name << " with resolution " << pxres << ", " << pyres << std::endl;
  window::init_glfw();

  if(xres==0 || yres==0){
    xres++;
    yres++;
  }

  reference=glfwCreateWindow(xres, yres, title.c_str(), NULL, NULL);
  if(reference==NULL){
    std::cerr << "err:w-window-initglfw-failed" << std::endl;
    window::kill_glfw();
    return;
  }

  set_current_context();

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cerr << "err:w-window-initglad-failed" << std::endl;
    return;
  }

  glViewport(0, 0, xres, yres);
  glfwSetFramebufferSizeCallback(reference, framebuffer_resize);

  return;
}

static void window::init_glfw()
{
  if(!window::glfw_initialized){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window::glfw_initialized=true;
  }

  return;
}

static void window::kill_glfw()
{
  if(window::glfw_initialized){
    glfwTerminate();

    window::glfw_initialized=false;
  }

  return;
}

static void window::framebuffer_resize(GLFWwindow* pref, int pxres, int pyres)
{
  glViewport(0, 0, pxres, pyres);
}

void window::set_current_context()
{
  glfwMakeContextCurrent(reference);
}

void window::set_title(std::string pt)
{
  title=pt;

  glfwSetWindowTitle(reference, title.c_str());
}

void window::set_resolution(int pxres, int pyres)
{
  xres=pxres;
  yres=pyres;

  glfwSetWindowSize(reference, xres, yres);
  window::framebuffer_resize(reference, xres, yres);
}

void window::set_render_loop_callback(void (*prfc)(window* pwin, void* pshd, void* pmsh))
{
  rendercallback=prfc;

  if(rendercallback==NULL){
    std::cerr << "err:w-window-rendercallback-null" << std::endl;
  }
}

void window::run_render_loop(void* pshd, void* pmsh)
{
  set_current_context();

  (*rendercallback)((window*)this, pshd, pmsh);

  if(rendercallback==NULL){
    std::cerr << "err:w-window-rendercallback-null" << std::endl;
  }

  glfwSwapBuffers(reference);
  glfwPollEvents();
}

bool window::is_open()
{
  return !(glfwWindowShouldClose(reference));
}

int window::get_resolution_x()
{
  return xres;
}

int window::get_resolution_y()
{
  return yres;
}

std::string window::get_title(){
  return title;
}

GLFWwindow* window::get_reference()
{
  return reference;
}

void (*window::get_render_loop_callback(void))(window* pwin, void* pshd, void* pmsh)
{
  return rendercallback;
}
