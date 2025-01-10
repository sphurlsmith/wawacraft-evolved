#include "libs.h"
#include "windef.h"
#include "render.h"
#include "shader.h"
#include "textures.h"
#include "mesh.h"

int DEFAULT_TEXTURE_RESOLUTION=32;
int DEFAULT_TEXTURE_CHANNELS=4;

void render(window* pwint, void* pshd, void* pmsh)
{
  shader* pshader=(shader*)pshd;
  mesh_base* pmesh=(mesh_base*)pmsh;

  pmesh->shader_set(pshader);
  // pmesh->vertex_attributes_bind(true);

  pmesh->render();
}

int main()
{
  window::init_glfw();

  window test(0, 0, "");
  render_environment test_env(&test, &render, {0.5, 0.5, 0.7, 1});

  shader test_shd("shd/wac_v_m3d_default.glsl", "shd/wac_f_m_default.glsl");
  texture test_tex("tex/wawa.png", DEFAULT_TEXTURE_RESOLUTION, DEFAULT_TEXTURE_RESOLUTION, DEFAULT_TEXTURE_CHANNELS, true);

  std::vector<float> verts=
  {
    -0.5, -0.5, 1, 1, 0, 0, 0, 0,
     0.5, -0.5, 1, 0, 1, 0, 1, 0,
    -0.5,  0.5, 1, 0, 0, 1, 0, 1,
     0.5,  0.5, 1, 1, 1, 1, 1, 1
  };

  std::vector<unsigned int> inds={0, 1, 2, 1, 2, 3};
  
  mesh_base test_mesh(verts, inds, true, true);
  
  test.set_title("Wawacraft:Evolved [v0.1.1-alpha indev] [OpenGL 3.3]");
  test.set_resolution(800, 600);

  test_mesh.shader_set(&test_shd);
  test_mesh.texture_set(&test_tex);
  
  while(test.is_open())
  {
    test_env.default_shader=test_mesh.shader_get();
    test_env.default_mesh=&test_mesh;
    test_env.screen_run_render_loop_instance();
  }

  window::kill_glfw();
  return 0;
}
