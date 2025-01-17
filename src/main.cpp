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
  
  if(pcmr!=NULL){
    pcamera->render_mesh(pmesh3d);
  }else{
    pmesh->render();
  }
}

int main()
{
  //testing_math();

  // trying out unit testing ofc
  
  window::init_glfw();

  window test(0, 0, "");
  render_environment test_env(&test, &render, {0.5, 0.5, 0.7, 1});

  shader test_shd("shd/wac_v_m_default.glsl", "shd/wac_f_m_default.glsl");
  shader test_sh3d("shd/wac_v_m3d_default.glsl", "shd/wac_f_m_default.glsl");
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
  mesh_3d test_3d(verts, inds, true, true, {0, 40*MATHLIB_DEGTORAD, 0}, {1, 0, 5}, 1);
  
  test.set_title("Wawacraft:Evolved [v0.1.1-alpha indev] [OpenGL 3.3]");
  test.set_resolution(800, 600);

  test_mesh.shader_set(&test_shd);
  test_mesh.texture_set(&test_tex);

  test_3d.shader_set(&test_sh3d);
  test_3d.texture_set(&test_tex);

  bool roll=false;
  while(test.is_open())
  {
    test_env.mesh=&test_mesh;
    test_env.mesh_3d=&test_3d;
    test_env.camera=&test_camera;
    
    test_env.screen_run_render_loop_instance(true);

    vector_3d vec=test_3d.position_get();
    vector_homogenous vecr(vec.x, vec.y, vec.z, 1);
    
    vecr=matrix::vector_multiply(matrix::multiply(*(test_camera.projection_matrix_get()), *(test_3d.model_matrix_get())), vecr);

    std::cout << vecr.x << " " << vecr.y << " " << vecr.z << " " << vecr.w << std::endl;
    
    roll=!roll;
  }

  window::kill_glfw();
  return 0;
}
