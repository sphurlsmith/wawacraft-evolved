#include "libs.h"
#include "shader.h"
#include "mesh.h"

mesh_base::mesh_base(std::vector<float> pvert, std::vector<unsigned int> pind, bool colors):
  m_vertices(pvert),
  m_indices(pind)
{
  buffers_generate();
  
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

  glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), &m_vertices.front(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(unsigned int), &m_indices.front(), GL_STATIC_DRAW);
}

void mesh_base::vertex_attributes_bind(bool colors_used)
{
  glBindVertexArray(m_vao);

  buffers_bind();

  int vpos=3;
  int vcol=0;

  if(colors_used){vcol=3;}
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (vpos+vcol)*sizeof(float), (void*)(0));
  glEnableVertexAttribArray(0);
  
  if(colors_used){
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (vpos+vcol)*sizeof(float), (void*)(vpos*sizeof(float)));
    glEnableVertexAttribArray(1);
  }
  
  glBindVertexArray(0);
}

void mesh_base::render()
{
  if(m_shader!=NULL){
    m_shader->activate();
  }else{
    std::cerr << "err:w-m_base-render-shader-null" << std::endl;
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
