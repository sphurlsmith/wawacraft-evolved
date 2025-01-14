#include "libs.h"
#include "windef.h"
#include "render.h"
#include "shader.h"
#include "textures.h"
#include "mesh.h"

int DEFAULT_TEXTURE_RESOLUTION=32;
int DEFAULT_TEXTURE_CHANNELS=4;

void render(window* pwint, void* pcmr, void* pmsh)
{
  mesh_base* pmesh=(mesh_base*)pmsh;
  mesh_3d* pmesh3d=(mesh_3d*)pmsh;

  camera* pcamera=(camera*)pcmr;
  
  if(pcmr==NULL){
    pmesh->render();
  }else{
    pcamera->render_mesh(pmsh);
  }
}

int main()
{
  window::init_glfw();

  window test(0, 0, "");
  render_environment test_env(&test, &render, {0.5, 0.5, 0.7, 1});

  shader test_shd("shd/wac_v_m3d_default.glsl", "shd/wac_f_m_default.glsl");
  texture test_tex("tex/wawa.png", DEFAULT_TEXTURE_RESOLUTION, DEFAULT_TEXTURE_RESOLUTION, DEFAULT_TEXTURE_CHANNELS, true);

  camera test_camera(800, 600, 50, 0.1, 10);
  
  std::vector<float> verts=
  {
    -0.5, -0.5, 0, 1, 0, 0, 0, 0,
     0.5, -0.5, 0, 0, 1, 0, 1, 0,
    -0.5,  0.5, 0, 0, 0, 1, 0, 1,
     0.5,  0.5, 0, 1, 1, 1, 1, 1
  };

  std::vector<unsigned int> inds={0, 1, 2, 1, 2, 3};
  
  mesh_base test_mesh(verts, inds, true, true);
  mesh_3d test_3d(verts, inds, false, true, {0, 0, 0}, {1, -1, 1}, 1);
  
  test.set_title("Wawacraft:Evolved [v0.1.1-alpha indev] [OpenGL 3.3]");
  test.set_resolution(800, 600);

  test_mesh.shader_set(&test_shd);
  test_mesh.texture_set(&test_tex);
  
  while(test.is_open())
  {
    test_env.mesh=&test_mesh;
    test_env.mesh_3d=&test_3d;
    test_env.camera=&test_camera;
    
    test_env.screen_run_render_loop_instance(true);

    test_3d.model_matrix_get()->debug_output();
    test_camera.projection_matrix_get()->debug_output();
  }

  window::kill_glfw();
  return 0;
}
