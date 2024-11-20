#ifndef WINDEF_H
#define WINDEF_H

#include "libs.h"

class window
{
 public:
  window(int pxres, int pyres, std::string name);

  static void init_glfw();
  static void kill_glfw();
  
  static void framebuffer_resize(GLFWwindow* pref, int pxres, int pyres);
  
  void set_current_context();
  void set_title(std::string pt);
  void set_resolution(int pxres, int pyres);
  void set_render_loop_callback(void (*prfc)(window* pwin));

  void run_render_loop();
  
  bool is_open();

  int get_resolution_x();
  int get_resolution_y();

  std::string get_title();
  
  GLFWwindow* get_reference();

  void (*get_render_loop_callback(void))(window* pwin);
  
 private:
  static bool glfw_initialized;
  
  int xres;
  int yres;

  std::string title;

  void (*rendercallback)(window* pwin);
  GLFWwindow* reference;
};

#endif
