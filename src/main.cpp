#include "libs.h"
#include "windef.h"
#include "control.h"
#include "render.h"
#include "shader.h"
#include "textures.h"
#include "voxel.h"
#include "mesh.h"

int DEFAULT_TEXTURE_RESOLUTION=32;
int DEFAULT_TEXTURE_CHANNELS=4;

int CLASSIC_TEXTURE_RESOLUTION=16;
int CLASSIC_TEXTURE_CHANNELS=3;

int SCLASS_TEXTURE_RESOLUTION=128;

float DEFAULT_SPEED=0.1;
float DEFAULT_TURN=4;

float DEFAULT_BLOCK_SIZE=(float)1/4;

key_callback KEY_W;
key_callback KEY_A;
key_callback KEY_S;
key_callback KEY_D;

key_callback KEY_ARROW_LEFT;
key_callback KEY_ARROW_RIGHT;
key_callback KEY_ARROW_UP;
key_callback KEY_ARROW_DOWN;

key_callback KEY_TAB;
key_callback KEY_ESC;

void render(window* pwint, void* pcmr, int argc, void** pmsh)
{
  mesh_base** pmesh=(mesh_base**)pmsh;
  mesh_3d** pmesh3d=(mesh_3d**)pmsh;
  
  camera* pcamera=(camera*)pcmr;
  
  if(pcmr!=NULL){
    for(int x=0; x<argc; x++){
      pcamera->render_mesh(*(pmesh3d+x));
    }
  }else{
    (*pmesh)->render();
  }
}

void move_camera(int argc, char** argv)
{
  camera** pcamptr=(camera**)argv;

  vector_3d pos=(**pcamptr).position_get();
  vector_3d rot=(**pcamptr).rotation_get();

  matrix view=*(**pcamptr).view_matrix_get();

  vector_3d u(view.m[0][0], view.m[0][1], view.m[0][2]);
  vector_3d v(view.m[1][0], view.m[1][1], view.m[1][2]);
  vector_3d n(view.m[2][0], view.m[2][1], view.m[2][2]);
  
  switch(argc){
  case 1:
    (**pcamptr).position_set(vector_3d::add(pos, vector_3d::scalar(n, DEFAULT_SPEED)));
    break;
  case 2:
    (**pcamptr).position_set(vector_3d::subtract(pos, vector_3d::scalar(n, DEFAULT_SPEED)));
    break;
  case 3:
    (**pcamptr).position_set(vector_3d::subtract(pos, vector_3d::scalar(u, DEFAULT_SPEED)));
    break;
  case 4:
    (**pcamptr).position_set(vector_3d::add(pos, vector_3d::scalar(u, DEFAULT_SPEED)));
    break;
  case 5:
    (**pcamptr).rotation_set({rot.x, rot.y+DEFAULT_TURN*MATHLIB_DEGTORAD, rot.z});
    break;
  case 6:
    (**pcamptr).rotation_set({rot.x, rot.y-DEFAULT_TURN*MATHLIB_DEGTORAD, rot.z});
    break;
  case 7:
    (**pcamptr).rotation_set({rot.x+MATHLIB_DEGTORAD, rot.y, rot.z});
    break;
  case 8:
    (**pcamptr).rotation_set({rot.x-MATHLIB_DEGTORAD, rot.y, rot.z});
    break;
  default:
    break;
  }
}

void tab(int argc, char** argv)
{
  switch(argc){
  case 0:
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    break;
  case 1:
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    break;
  default:
    break;
  }
}

int main()
{
  window::init_glfw();

  window test(800, 600, "");
  test.set_current_context();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  
  render_environment test_env(&test, &render, {0.5, 0.5, 0.7, 1});

  shader test_shd("shd/wac_v_m_default.glsl", "shd/wac_f_m_default.glsl");
  shader test_sh3d("shd/wac_v_m3d_default.glsl", "shd/wac_f_m_default.glsl");
  shader nocol3d("shd/wac_v_m3d_nocol.glsl", "shd/wac_f_m_nocol.glsl");

  texture test_tex("tex/grass.png", DEFAULT_TEXTURE_RESOLUTION, DEFAULT_TEXTURE_RESOLUTION, DEFAULT_TEXTURE_CHANNELS, true);
  texture wawatex("tex/wawa.png", DEFAULT_TEXTURE_RESOLUTION, DEFAULT_TEXTURE_RESOLUTION, DEFAULT_TEXTURE_CHANNELS, true);
  texture unitex("tex/uni.png", DEFAULT_TEXTURE_RESOLUTION, DEFAULT_TEXTURE_RESOLUTION, DEFAULT_TEXTURE_CHANNELS, true);

  test_shd.uniform_set_int("tex", 0);
  test_sh3d.uniform_set_int("tex", 0);

  camera test_camera(800, 600, 60, 0.1, 256, {0, 0, -1}, {0, 0, 0});
  texture* texpack[4]=
    {
      NULL,
      &test_tex,
      &wawatex,
      &unitex
    };

  texture* texpack2[4]=
    {
      NULL,
      &wawatex,
      &unitex,
      &test_tex
    };
  
  chunk my_chunk({1, 0, 0}, texpack, &nocol3d);
  chunk my_chunk2({0, 0, 0}, texpack2, &nocol3d);

  my_chunk2.mesh_form();
  my_chunk.mesh_form();
  
  mesh_3d* meshes[2]={
    my_chunk2.mesh_get(),
    my_chunk.mesh_get()
  };
  
  test.set_title("Wawacraft:Evolved [v0.1.1-alpha indev] [OpenGL 3.3]");

  KEY_W.keycode=GLFW_KEY_W;
  KEY_W.callback=&move_camera;
  
  KEY_A.keycode=GLFW_KEY_A;
  KEY_A.callback=&move_camera;

  KEY_S.keycode=GLFW_KEY_S;
  KEY_S.callback=&move_camera;

  KEY_D.keycode=GLFW_KEY_D;
  KEY_D.callback=&move_camera;

  KEY_ARROW_LEFT.keycode=GLFW_KEY_LEFT;
  KEY_ARROW_LEFT.callback=&move_camera;
  
  KEY_ARROW_RIGHT.keycode=GLFW_KEY_RIGHT;
  KEY_ARROW_RIGHT.callback=&move_camera;

  KEY_ARROW_UP.keycode=GLFW_KEY_UP;
  KEY_ARROW_UP.callback=&move_camera;

  KEY_ARROW_DOWN.keycode=GLFW_KEY_DOWN;
  KEY_ARROW_DOWN.callback=&move_camera;

  KEY_TAB.keycode=GLFW_KEY_TAB;
  KEY_TAB.callback=&tab;

  KEY_ESC.keycode=GLFW_KEY_ESCAPE;
  KEY_ESC.callback=&tab;
  
  char* camptr=(char*)&test_camera;
  char** camptrptr=&camptr;

  vector_3d rot(0, 0, 0);
  
  bool roll=false;
  while(test.is_open())
  {
    test_env.mesh_3d=meshes;
    test_env.camera=&test_camera;
    
    test_env.screen_run_render_loop_instance(2, true);
    
    key_callback_execute_press(test.get_reference(), &KEY_ARROW_LEFT, 5, camptrptr);
    key_callback_execute_press(test.get_reference(), &KEY_ARROW_RIGHT, 6, camptrptr);
    key_callback_execute_press(test.get_reference(), &KEY_ARROW_UP, 7, camptrptr);
    key_callback_execute_press(test.get_reference(), &KEY_ARROW_DOWN, 8, camptrptr);
    
    key_callback_execute_press(test.get_reference(), &KEY_W, 1, camptrptr);
    key_callback_execute_press(test.get_reference(), &KEY_S, 2, camptrptr);
    key_callback_execute_press(test.get_reference(), &KEY_A, 3, camptrptr);
    key_callback_execute_press(test.get_reference(), &KEY_D, 4, camptrptr);

    key_callback_execute_press(test.get_reference(), &KEY_TAB, 0, NULL);
    key_callback_execute_press(test.get_reference(), &KEY_ESC, 1, NULL);
    
    roll=!roll;
  }

  window::kill_glfw();
  return 0;
}
