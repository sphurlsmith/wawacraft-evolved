#include "libs.h"
#include "mesh.h"

// implementation of the mesh.h header file.

// constructor of wc_BasicMesh. which takes in a vertex and index vector
// initializing its local arrays, and calls to set up the mesh
wc_BasicMesh::wc_BasicMesh(std::vector<float> vertexpar, std::vector<unsigned int> indexpar){
  this->vertices=vertexpar;
  this->indices=indexpar;

  setupMesh(); // relinquishing control to the setupMesh function
}

// nothing is done in the destructor for now
wc_BasicMesh::~wc_BasicMesh(){
  
}

// setting generic vertex attributes. static for convenience
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

// initializing the OpenGL objects: VAO, VBO, and EBO
void wc_BasicMesh::initializeBufferObjects(){
  // initializing the vertex array object
  glGenVertexArrays(1, &(this->VAO));

  // initializing the vertex buffer and element buffer object
  glGenBuffers(1, &(this->VBO));
  glGenBuffers(1, &(this->EBO));

  initialized=true; // turning on the flag for future calls of setupMesh
}

// function that binds in the vertex and index arrays.
void wc_BasicMesh::configureBufferObjects(){
  // feeding in VBO data
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices.front(), GL_STATIC_DRAW);

  // feeding in EBO data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
}

void wc_BasicMesh::setupMesh(){
  // placing the setup function in a subroutine for convenience
  // and also because we want to avoid registering our objects twice
  if(!initialized){
    initializeBufferObjects();
  }

  // setting up the real runtime data
  glBindVertexArray(VAO);
  configureBufferObjects(); // feeding in array data from vertex & index arrays
  setVertexAttributes();    // setting the vertex attributes for our instance
  glBindVertexArray(0);     // unbinding the VAO
}

// function to render our instance of wc_BasicMesh
// doesnt integrate textures or anything.
void wc_BasicMesh::renderMesh(){
  glBindVertexArray(VAO); // uses VAO binds
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // render
  glBindVertexArray(0); // unbinds VAO. simple as
}
