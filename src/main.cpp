#include "libs.h"
#include "windef.h"
#include "render.h"
#include "shader.h"
#include "mesh.h"

void render(window* pwint, void* pshd, void* pmsh)
{
  shader* pshader=(shader*)pshd;
  mesh_base* pmesh=(mesh_base*)pmsh;

  pmesh->shader_set(pshader);
  pmesh->vertex_attributes_bind(true);

  pmesh->render();
}

int main()
{
  window::init_glfw();

  window test(0, 0, "");
  render_environment test_env(&test, &render, {0.5, 0.5, 0.7, 1});

  shader test_shd("shd/wac_v_m_default.glsl", "shd/wac_f_m_default.glsl");

  std::vector<float> verts=
  {
    0,    0.5,  0, 1, 0, 0,
    0.5,  -0.5, 0, 0, 1, 0,
    -0.5, -0.5, 0, 0, 0, 1
  };

  std::vector<unsigned int> inds={0, 1, 2};
  
  mesh_base test_mesh(verts, inds, true);
  
  test.set_title("Wawacraft:Evolved [v0.1.1-alpha indev] [OpenGL 3.3]");
  test.set_resolution(800, 600);

  test_env.default_shader=&test_shd;
  test_env.default_mesh=&test_mesh;
  
  while(test.is_open())
  {
    test_env.screen_run_render_loop_instance();
  }

  window::kill_glfw();
  return 0;
}
