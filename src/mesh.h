#ifndef MESH_H
#define MESH_H

#include "libs.h"

// the mesh.h header provides the classes used to create render-friendly meshes
// as of now it contains the wc_BasicMesh class, which creates a mesh with
// optional texturing and no integrated options for color overlaying.

// a basic mesh class that provides the utility of a mesh that can be textured
// and colored. It has no integrated color overlaying options, and no perspective
// projection.
class wc_BasicMesh{
 public:
  // the constructor, which initializes a mesh in OpenGL that is ready for
  // rendering. It initializes the vectors storing the vertex and index arrays
  // then relinquishes control to wc_BasicMesh::setupMesh();
  wc_BasicMesh(std::vector<float> vertices, std::vector<unsigned int> indices);
  ~wc_BasicMesh(); // nothing needs to be done here yet.

  // a function that sets the default vertex attributes of a mesh, with
  // vertex, color, and texture data only.
  static void setVertexAttributes();

  // a function that initializes the VAO, VBO, and EBO openGL objects.
  void initializeBufferObjects();
  // this function binds the vertex array and index array data to the instance
  // VAO.
  void configureBufferObjects();

  // sets up a mesh, initializing and configuring the VAO and its buffer objects
  void setupMesh();
  // renders the mesh using the index array. You can precede these by
  // activating the texture and shader you like when rendering, but as I said,
  // it isnt integrated
  void renderMesh();
  
 private:
  bool initialized; // flag for checking if our opengl objects are registered

  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;

  // the vertex and index arrays are stored as vectors since it makes it
  // easier to manage and take care of a mesh, given that it needs to change
  // its data at any given time.
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
};

#endif
