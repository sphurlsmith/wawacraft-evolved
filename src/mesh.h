#ifndef MESH_H
#define MESH_H

#include "libs.h"
#include "shader.h"

class mesh_base
{
 public:
  mesh_base(std::vector<float> pvert, std::vector<unsigned int> pind, bool colors);

  void buffers_generate();
  void buffers_bind();
  
  void vertex_attributes_bind(bool colors_used);

  void render();

  void vertices_set(std::vector<float> pvert);
  void indices_set(std::vector<unsigned int> pind);

  void shader_set(shader* pshader);
  
  std::vector<float> vertices_get();
  std::vector<unsigned int> indices_get();

  shader* shader_get();
  
 protected:
  unsigned int m_vao;
  unsigned int m_vbo;
  unsigned int m_ebo;

  std::vector<float> m_vertices;
  std::vector<unsigned int> m_indices;

  shader* m_shader;
};

#endif
