#include "libs.h"
#include "shader.h"
#include "mesh.h"

mesh_base::mesh_base(std::vector<float> pvert, std::vector<unsigned int> pind, bool colors):
  m_vertices(pvert),
  m_indices(pind)
{
  buffers_generate();
  buffers_bind();
  
  vertex_attributes_bind(colors);
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

  glBufferData(GL_ARRAY_BUFFER, )
}

void mesh_base::vertex_attributes_bind(bool colors)
{
  int attr_elements=3;
  
  if(colors){attr_elements+=3}

  
}
