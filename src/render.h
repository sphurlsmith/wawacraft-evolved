#ifndef RENDER_H
#define RENDER_H

#include "libs.h"
#include "windef.h"

struct color4e
{
  float r;
  float g;
  float b;
  float a;
};

struct color3e
{
  float r;
  float g;
  float b;
};

class render_environment
{
 public:
  render_environment(window* pwin, void (*prlc)(window* p), color4e pc);

  void target_window_set(window* pwin);
  void clear_color_set(color4e pc);
  
  void render_loop_callback_set(void (*prlc)(window* p));
  void (*render_loop_callback_get(void))(window* p);
  
  void screen_clear();
  void screen_call_render_callback();
  void screen_run_render_loop_instance();

  window* target_window_get();
  color4e clear_color_get();
  
 private:
  window* targetwindow;
  void (*renderloopcallback)(window* p);
  
  color4e clearcolor;
};

#endif
