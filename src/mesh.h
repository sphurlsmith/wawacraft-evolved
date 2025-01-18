#ifndef MESH_H
#define MESH_H

#include "libs.h"
#include "mathlib.h"
#include "shader.h"
#include "textures.h"

class mesh_base
{
 public:
  mesh_base(std::vector<float> pvert, std::vector<unsigned int> pind, bool colors, bool textures);

  void buffers_generate();
  void buffers_bind();
  
  void vertex_attributes_bind(bool colors_used, bool textures_used);

  void render();

  void vertices_set(std::vector<float> pvert);
  void indices_set(std::vector<unsigned int> pind);

  void shader_set(shader* pshader);
  void texture_set(texture* ptexture);
  
  std::vector<float> vertices_get();
  std::vector<unsigned int> indices_get();

  shader* shader_get();
  texture* texture_get();
  
 protected:
  unsigned int m_vao;
  unsigned int m_vbo;
  unsigned int m_ebo;

  std::vector<float> m_vertices;
  std::vector<unsigned int> m_indices;

  shader* m_shader;
  texture* m_texture;
};

class mesh_3d:public mesh_base
{
 public:
  mesh_3d(std::vector<float> pvert, std::vector<unsigned int> pind, bool colors, bool textures, vector_3d protation, vector_3d ptranslation, float pscale);

  void scale_set(float pscale);
  void rotation_set(vector_3d protation);
  void position_set(vector_3d ptranslation);
  
  void model_matrix_form();

  float scale_get();
  
  float rotation_x_get();
  float rotation_y_get();
  float rotation_z_get();

  vector_3d position_get();
  
  matrix* model_matrix_get();
  
 protected:
  float m_scale;
  
  float m_rotation_x;
  float m_rotation_y;
  float m_rotation_z;
  
  vector_3d m_position;

  matrix m_model;
};

class camera
{
 public:
  camera(int paspectx, int paspecty, float pfov, float pnear, float pfar, vector_3d pposition, vector_3d protation);

  void render_mesh(mesh_3d* mesh);
  
  void resolution_set(int px, int py);
  void fov_set(float pfov);
  
  void plane_near_set(float p);
  void plane_far_set(float p);

  void position_set(vector_3d pposition);
  void rotation_set(vector_3d protation);
  
  void projection_matrix_form();
  void view_matrix_form();

  int resolution_x_get();
  int resolution_y_get();

  float fov_get();

  float plane_near_get();
  float plane_far_get();

  vector_3d position_get();
  vector_3d rotation_get();

  matrix* projection_matrix_get();
  matrix* view_matrix_get();
  
 private:
  int c_resolution_x;
  int c_resolution_y;

  float c_fov;
  
  float c_near;
  float c_far;

  vector_3d c_position;
  vector_3d c_rotation;
  
  matrix c_projection;
  matrix c_view;
};

#endif
