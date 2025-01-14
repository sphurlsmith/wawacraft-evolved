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

void testing_math()
{
  // QUATERNION TESTING

  std::cout << "UNIT TESTING WAWACRAFT:EVOLVED MATHLIB" << std::endl;
  std::cout << "QUATERNION TESTING" << std::endl;

  std::cout << "INITIALIZING QUAT A WITH VALUES {1, 2, 3, 4}" << std::endl;
  quat a(1, 2, 3, 4);

  std::cout << "A: {" << a.w << ", " << a.i << ", " << a.j << ", " << a.k << "}" << std::endl;

  int succeeded_tests=0;
  
  std::cout << "[1]: Testing norm... ";
  if(quat::norm(a)==(float)sqrt(30)){
    std::cout << "OK" << std::endl;
    succeeded_tests++;
  }else{std::cout << "NO" << std::endl;}
  
  std::cout << "[2]: Testing conjugate product... ";
  if(quat::norm_nosqrt(a)==30){
    std::cout << "OK" << std::endl;
    succeeded_tests++;
  }else{std::cout << "NO" << std::endl;}
  
  std::cout << "[3]: Testing conjugate... ";
  if(quat::conjugate(a).w==a.w && quat::conjugate(a).i==-a.i &&
     quat::conjugate(a).j==-a.j && quat::conjugate(a).k==-a.k){
    std::cout << "OK" << std::endl;
    succeeded_tests++;
  }else{std::cout << "NO" << std::endl;}

  std::cout << "[4]: Testing normalized quaternion... ";
  std::cout << (quat::normalize(a).w*quat::normalize(a).w+
		quat::normalize(a).i*quat::normalize(a).i+
		quat::normalize(a).j*quat::normalize(a).j+
		quat::normalize(a).k*quat::normalize(a).k)*100 << "% ";
  if((quat::normalize(a).w*quat::normalize(a).w+
      quat::normalize(a).i*quat::normalize(a).i+
      quat::normalize(a).j*quat::normalize(a).j+
      quat::normalize(a).k*quat::normalize(a).k)*100>90){
    std::cout << "OK" << std::endl;
    succeeded_tests++;
  }else{std::cout << "NO" << std::endl;}

  std::cout << "[5]: Testing inverse quaternion... ";
  std::cout << (quat::inverse(a).w+quat::inverse(a).i+
		quat::inverse(a).j+quat::inverse(a).k)*30*100 << "% ";
  if((quat::inverse(a).w+quat::inverse(a).i+
      quat::inverse(a).j+quat::inverse(a).k)*30*100>90){
    std::cout << "OK" << std::endl;
    succeeded_tests++;
  }else{std::cout << "NO" << std::endl;}

  std::cout << "[6]: Testing (faux)negated quaternion... ";
  if(quat::negate(a).w==-a.w && quat::negate(a).i==-a.i &&
     quat::negate(a).j==-a.j && quat::negate(a).k==-a.k){
    std::cout << "OK" << std::endl;
    succeeded_tests++;
  }else{std::cout << "NO" << std::endl;}

  std::cout << "If test 4, and 5 are correct, the scalar function works. :3" << std::endl;

  std::cout << "[7]: Testing quaternion addition... ";
  quat b(4, 3, 2, 1);
  quat c=quat::add(a, b);
  if(c.w==5 && c.i==5 && c.j==5 && c.k==5){
    std::cout << "OK" << std::endl;
    succeeded_tests++;
  }else{std::cout << "NO" << std::endl;}

  std::cout << "[8]: Testing quaternion subtraction... ";
  c=quat::subtract(b, a);
  if(c.w==3 && c.i==1 && c.j==-1 && c.k==-3){
    std::cout << "OK" << std::endl;
    succeeded_tests++;
  }else{std::cout << "NO" << std::endl;}

  std::cout << "[9]: Testing quaternion product... ";
  c=quat::product(a, b);
  if(c.w==-12 && c.i==6 && c.j==24 && c.k==12){
    std::cout << "OK" << std::endl;
    succeeded_tests++;
  }else{std::cout << "NO" << std::endl;}
  std::cout << "{" << quat::product(a, b).w << ", "
	    << quat::product(a, b).i << ", "
	    << quat::product(a, b).j << ", "
	    << quat::product(a, b).k << "}" << std::endl;
  
  std::cout << succeeded_tests << " out of 9 Tests succeeded" << std::endl;
}

int main()
{
  testing_math();
  return 0;

  // trying out unit testing ofc
  
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
