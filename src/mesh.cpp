#include "libs.h"
#include "mesh.h"

wc_BasicMesh::wc_BasicMesh(std::vector<float> vertexpar, std::vector<unsigned int> indexpar){
  this->vertices=vertexpar;
  this->indices=indexpar;

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
}

void wc_BasicMesh::initializeBufferObjects(){
  // initializing the vertex array object
  glGenVertexArrays(1, &(this->VAO));

  // initializing the vertex buffer object and the element buffer object
  glGenBuffers(1, &(this->VBO));
  glGenBuffers(1, &(this->EBO));
}

void wc_BasicMesh::configureBufferObjects(){
  // feeding in VBO data
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices.front(), GL_STREAM_DRAW);

  // feeding in EBO data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices.front(), GL_STREAM_DRAW);
}

void wc_BasicMesh::setupMesh(){
  // placing the setup function in a subroutine for convenience
  initializeBufferObjects();

  // setting up the real runtime data
  // notice how I put the vertex binding commands straight up around it, and not within the functions? This is to keep the class as simple and basic as it could possibly be.
  glBindVertexArray(VAO);
  configureBufferObjects();
  setVertexAttributes();
  glBindVertexArray(0);
}

void wc_BasicMesh::renderMesh(unsigned int t=0){
  glBindTexture(GL_TEXTURE_2D, &t);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
