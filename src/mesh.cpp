#include "libs.h"
#include "mesh.h"

wc_BasicMesh::wc_BasicMesh(std::vector<float> vertexpar, std::vector<unsigned int> indexpar){
  this->vertices=vertexpar;
  this->indices=indexpar;

  setVertexAttributes();
  setupMesh();
}

wc_BasicMesh::~wc_BasicMesh(){
  
}

static void wc_BasicMesh::setVertexAttributes(){
  // since this is just a basic mesh like we did before, it wont have anything too fancy.
  
  // vertex location attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // color data attributes
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  // texture data attributes
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
  glEnableVertexAttribArray(2);
}

void wc_BasicMesh::initializeBufferObjects(){
  // initializing the vertex array object
  glGenVertexArrays(1, &(this->VAO));

  // initializing the vertex buffer and element buffer object
  glGenBuffers(1, &(this->VBO));
  glGenBuffers(1, &(this->EBO));
}

void wc_BasicMesh::configureBufferObjects(){
  // feeding in VBO data
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices.front(), GL_STATIC_DRAW);

  // feeding in EBO data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
  glBindVertexArray(0);
}

void wc_BasicMesh::setupMesh(){
  // placing the setup function in a subroutine for convenience
  initializeBufferObjects();

  // setting up the real runtime data
  glBindVertexArray(VAO);
  configureBufferObjects();
  setVertexAttributes();
  glBindVertexArray(0);
}

void wc_BasicMesh::renderMesh(){
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
