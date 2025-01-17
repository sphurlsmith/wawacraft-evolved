#include "libs.h"
#include "windef.h"
#include "render.h"

render_environment::render_environment(window* pwin, void (*prlc)(window* p), color4e pc):
  mesh(NULL),
  mesh_3d(NULL),
  camera(NULL)
{
  target_window_set(pwin);
  render_loop_callback_set(prlc);
  clear_color_set(pc);
  
  if(pwin==NULL){
    std::cerr << "err:w-render_environment-init-targetwindow-null" << std::endl;
  }

  if(prlc==NULL){
    std::cerr << "err:w-render_environment-init-renderloopcallback-null" << std::endl;
  }
}

void render_environment::target_window_set(window* pwin)
{
  targetwindow=pwin;

  if(targetwindow==NULL){
    std::cerr << "err:w-render_environment-targetwindow-null" << std::endl;
  }
}

void render_environment::clear_color_set(color4e pc)
{
  clearcolor=pc;
}

void render_environment::render_loop_callback_set(void (*prlc)(window* p))
{
  renderloopcallback=prlc;
  targetwindow->set_render_loop_callback(prlc);

  if(renderloopcallback==NULL){
    std::cerr << "err:w-render_environment-renderloopcallback-null" << std::endl;
  }

  if(targetwindow==NULL){
    std::cerr << "err:w-render_environment-targetwindow-null" << std::endl;
  }
}

void (*render_environment::render_loop_callback_get(void))(window* p)
{
  return renderloopcallback;
}

void render_environment::screen_clear()
{
  targetwindow->set_current_context();

  glClearColor(clearcolor.r, clearcolor.g, clearcolor.b, clearcolor.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void render_environment::screen_call_render_callback(bool use_3d){
  if(targetwindow==NULL){
    std::cerr << "err:w-render_environment-targetwindow-null" << std::endl;
  }

  if(targetwindow->get_render_loop_callback()==NULL){
    std::cerr << "err:w-render_environment:window-rendercallback-null" << std::endl;
  }

  if(targetwindow!=NULL && targetwindow->get_render_loop_callback()!=NULL){
    if(use_3d){
      targetwindow->run_render_loop(camera, mesh_3d);
    }else{
      targetwindow->run_render_loop(NULL, mesh);
    }
  }
}

void render_environment::screen_run_render_loop_instance(bool use_3d)
{
  screen_clear();
  screen_call_render_callback(use_3d);
}

window* render_environment::target_window_get()
{
  return targetwindow;
}

color4e render_environment::clear_color_get()
{
  return clearcolor;
}
