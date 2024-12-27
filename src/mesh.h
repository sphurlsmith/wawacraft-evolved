#ifndef MESH_H
#define MESH_H

#include "libs.h"
#include "shader.h"

class mesh_base
{
 public:
  mesh_base();

  void buffers_generate();
  void buffers_bind();
  
  void vertex_attributes_bind(bool colors);

  void render(shader* pshader);
  
 protected:
  unsigned int m_vao;
  unsigned int m_vbo;
  unsigned int m_ebo;

  std::vector<float> m_vertices;
  std::vector<unsigned int> m_indices;
};

#endif
