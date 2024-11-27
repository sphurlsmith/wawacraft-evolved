#include "libs.h"
#include "windef.h"
#include "render.h"

void render(window* pwint)
{
  
}

int main()
{
  window::init_glfw();

  window test(0, 0, "");
  render_environment test_env(&test, &render, {0.5, 0.5, 0.7, 1});
  
  test.set_title("Wawacraft Evolved [v0.1.1-alpha indev] [OpenGL 3.3]");
  test.set_resolution(800, 600);
  
  while(test.is_open())
  {
    test_env.screen_run_render_loop_instance();
  }

  window::kill_glfw();
  return 0;
}
