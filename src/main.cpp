#include "libs.h"
#include "windef.h"

void render(window* pwint)
{
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
  window::init_glfw();

  window test(0, 0, "");
  
  test.set_title("Wawacraft Evolved [v0.1.1-alpha indev] [OpenGL 3.3]");
  test.set_resolution(800, 600);

  test.set_render_loop_callback(&render);
  
  while(test.is_open())
  {
    test.run_render_loop();
  }

  window::kill_glfw();
  return 0;
}
