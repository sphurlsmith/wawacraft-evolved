#ifndef MESH_H
#define MESH_H

#include "libs.h"

class wc_BasicMesh{
 public:
  wc_BasicMesh(std::vector<float> vertices, std::vector<unsigned int> indices);
  ~wc_BasicMesh();

  static void setVertexAttributes();
  
  void initializeBufferObjects();
  void configureBufferObjects();

  void setupMesh();
  void renderMesh();
  
 private:
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
  
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
};

#endif
