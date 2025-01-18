#include "libs.h"
#include "shader.h"
#include "textures.h"
#include "mesh.h"

mesh_base::mesh_base(std::vector<float> pvert, std::vector<unsigned int> pind, bool colors, bool textures):
  m_vertices(pvert),
  m_indices(pind)
{
  buffers_generate();
  
  vertex_attributes_bind(colors, textures);
}

void mesh_base::buffers_generate()
{
  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ebo);
  glGenVertexArrays(1, &m_vao);
}

void mesh_base::buffers_bind()
{ 
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

  glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), &m_vertices.front(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(unsigned int), &m_indices.front(), GL_STATIC_DRAW);
}

void mesh_base::vertex_attributes_bind(bool colors_used, bool textures_used)
{
  glBindVertexArray(m_vao);

  buffers_bind();

  int vpos=3;
  int vcol=0;
  int vtex=0;

  if(colors_used){vcol=3;}
  if(textures_used){vtex=2;}
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (vpos+vcol+vtex)*sizeof(float), (void*)(0));
  glEnableVertexAttribArray(0);
  
  if(colors_used){
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (vpos+vcol+vtex)*sizeof(float), (void*)(vpos*sizeof(float)));
    glEnableVertexAttribArray(1);
  }

  if(textures_used){
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (vpos+vcol+vtex)*sizeof(float), (void*)((vpos+vcol)*sizeof(float)));
    glEnableVertexAttribArray(2);
  }
  
  glBindVertexArray(0);
}

void mesh_base::render()
{
  if(m_shader!=NULL){
    int val;
    glGetIntegerv(GL_CURRENT_PROGRAM, &val);
    if(val!=m_shader->get_id()){
      m_shader->activate();
    }
  }else{
    std::cerr << "err:w-m_base-render-shader-null" << std::endl;
  }

  if(m_texture!=NULL){
    m_texture->texture_object_use();
  }else{
    std::cerr << "err:w-m_base-render-texture-null" << std::endl;
  }
  
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void mesh_base::vertices_set(std::vector<float> pvert)
{
  m_vertices=pvert;
}

void mesh_base::indices_set(std::vector<unsigned int> pind)
{
  m_indices=pind;
}

void mesh_base::shader_set(shader* pshader)
{
  if(pshader!=NULL){
    m_shader=pshader;
  }else{
    std::cerr << "err:w-mesh_base-shader-null" << std::endl;
  }
}

void mesh_base::texture_set(texture* ptexture)
{
  if(ptexture!=NULL){
    m_texture=ptexture;
  }else{
    std::cerr << "err:w-mesh_base-texture-null" << std::endl;
  }
}

std::vector<float> mesh_base::vertices_get()
{
  return m_vertices;
}

std::vector<unsigned int> mesh_base::indices_get()
{
  return m_indices;
}

shader* mesh_base::shader_get()
{
  return m_shader;
}

texture* mesh_base::texture_get()
{
  return m_texture;
}

mesh_3d::mesh_3d(std::vector<float> pvert, std::vector<unsigned int> pind, bool colors, bool textures, vector_3d protation, vector_3d ptranslation, float pscale):
  mesh_base(pvert, pind, colors, textures),
  m_position(ptranslation),
  m_rotation_x(protation.x),
  m_rotation_y(protation.y),
  m_rotation_z(protation.z),
  m_scale(pscale),
  m_model(matrix::base()){
  model_matrix_form();
}

void mesh_3d::scale_set(float pscale)
{
  m_scale=pscale;
}

void mesh_3d::rotation_set(vector_3d protation)
{
  m_rotation_x=protation.x;
  m_rotation_y=protation.y;
  m_rotation_z=protation.z;
}

void mesh_3d::position_set(vector_3d ptranslation)
{
  m_position=ptranslation;
}

void mesh_3d::model_matrix_form()
{
  m_model=matrix::model(m_rotation_x, m_rotation_y, m_rotation_z, m_scale, m_position);
}

float mesh_3d::scale_get()
{
  return m_scale;
}

float mesh_3d::rotation_x_get()
{
  return m_rotation_x;
}

float mesh_3d::rotation_y_get()
{
  return m_rotation_y;
}

float mesh_3d::rotation_z_get()
{
  return m_rotation_z;
}

vector_3d mesh_3d::position_get()
{
  return m_position;
}

matrix* mesh_3d::model_matrix_get()
{
  return &m_model;
}

camera::camera(int paspectx, int paspecty, float pfov, float pnear, float pfar, vector_3d pposition, vector_3d protation):
  c_resolution_x(paspectx),
  c_resolution_y(paspecty),
  c_fov(pfov),
  c_near(pnear),
  c_far(pfar),
  c_position(pposition),
  c_rotation(protation),
  c_projection(matrix::base()),
  c_view(matrix::base()){
  projection_matrix_form();
  view_matrix_form();
}

void camera::render_mesh(mesh_3d* mesh)
{
  projection_matrix_form();
  view_matrix_form();
  mesh->model_matrix_form();
  
  mesh->shader_get()->activate();
  mesh->shader_get()->uniform_set_matrix("mod", &(mesh->model_matrix_get()->m[0][0]), false);
  mesh->shader_get()->uniform_set_matrix("view", &(c_view.m[0][0]), false);
  mesh->shader_get()->uniform_set_matrix("proj", &(c_projection.m[0][0]), false);
  
  mesh->render();
}

void camera::resolution_set(int px, int py)
{
  c_resolution_x=px;
  c_resolution_y=py;
}

void camera::fov_set(float pfov)
{
  c_fov=pfov;
}

void camera::position_set(vector_3d pposition)
{
  c_position=pposition;
}

void camera::rotation_set(vector_3d protation)
{
  c_rotation=protation;
}

void camera::plane_near_set(float p)
{
  c_near=p;
}

void camera::plane_far_set(float p)
{
  c_far=p;
}

vector_3d camera::position_get()
{
  return c_position;
}

vector_3d camera::rotation_get()
{
  return c_rotation;
}

void camera::projection_matrix_form()
{
  float aspect=c_resolution_x/c_resolution_y;
  c_projection=matrix::projection(c_near, c_far, c_fov, aspect);
}

void camera::view_matrix_form()
{
  quat rotorx(cos(c_rotation.x/2), sin(c_rotation.x/2), 0, 0);
  quat rotory(cos(c_rotation.y/2), 0, sin(c_rotation.y/2), 0);
  quat rotorz(cos(c_rotation.z/2), 0, 0, sin(c_rotation.z/2));

  c_view=matrix::multiply(matrix::translation(vector_3d::negate(c_position)), matrix::quaternion(quat::product(rotorz, quat::product(rotory, rotorx))));
}

int camera::resolution_x_get()
{
  return c_resolution_x;
}

int camera::resolution_y_get()
{
  return c_resolution_y;
}

float camera::fov_get()
{
  return c_fov;
}

float camera::plane_near_get()
{
  return c_near;
}

float camera::plane_far_get()
{
  return c_far;
}

matrix* camera::projection_matrix_get()
{
  return &c_projection;
}

matrix* camera::view_matrix_get()
{
  return &c_view;
}
