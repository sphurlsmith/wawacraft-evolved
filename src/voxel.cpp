#include "libs.h"
#include "mathlib.h"
#include "shader.h"
#include "textures.h"
#include "mesh.h"
#include "render.h"
#include "voxel.h"

int voxel::DEFAULT_TEXTURE_RESOLUTION=32;
int voxel::DEFAULT_TEXTURE_CHANNELS=4;

voxel::voxel():
  v_size(1),
  v_position({0, 0, 0}),
  v_type(VOX_NONE){
  
}

voxel::voxel(float psize, voxcoord pposition, voxtype ptype, shader* pshader, texture* ptexture):
  v_size(psize),
  v_position(pposition),
  v_type(ptype){
  mesh_form(pshader, ptexture);
}

void voxel::position_set(voxcoord pposition)
{
  v_position=pposition;
}

void voxel::type_set(voxtype ptype)
{
  v_type=ptype;
}

void voxel::mesh_form(shader* pshader, texture* ptexture)
{
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  float s=v_size/2;

  float x=v_position.x;
  float y=v_position.y;
  float z=v_position.z;

  int face=0;

  vertices.insert(vertices.end(), {(-s), (-s), (+s), 1, 0});
  vertices.insert(vertices.end(), {(+s), (-s), (+s), 0, 0});
  vertices.insert(vertices.end(), {(+s), (+s), (+s), 0, 1});
  vertices.insert(vertices.end(), {(-s), (+s), (+s), 1, 1});
  
  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
    
  vertices.insert(vertices.end(), {(-s), (-s), (-s), 0, 0});
  vertices.insert(vertices.end(), {(+s), (-s), (-s), 1, 0});
  vertices.insert(vertices.end(), {(+s), (+s), (-s), 1, 1});
  vertices.insert(vertices.end(), {(-s), (+s), (-s), 0, 1});

  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
  
  vertices.insert(vertices.end(), {(+s), (-s), (-s), 0, 0});
  vertices.insert(vertices.end(), {(+s), (-s), (+s), 1, 0});
  vertices.insert(vertices.end(), {(+s), (+s), (+s), 1, 1});
  vertices.insert(vertices.end(), {(+s), (+s), (-s), 0, 1});

  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
  
  vertices.insert(vertices.end(), {(-s), (+s), (-s), 1, 1});
  vertices.insert(vertices.end(), {(-s), (+s), (+s), 0, 1});
  vertices.insert(vertices.end(), {(-s), (-s), (+s), 0, 0});
  vertices.insert(vertices.end(), {(-s), (-s), (-s), 1, 0});

  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
  
  vertices.insert(vertices.end(), {(-s), (+s), (+s), 0, 1});
  vertices.insert(vertices.end(), {(+s), (+s), (+s), 1, 1});
  vertices.insert(vertices.end(), {(+s), (+s), (-s), 1, 0});
  vertices.insert(vertices.end(), {(-s), (+s), (-s), 0, 0});

  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
  
  vertices.insert(vertices.end(), {(-s), (-s), (+s), 0, 0});
  vertices.insert(vertices.end(), {(+s), (-s), (+s), 1, 0});
  vertices.insert(vertices.end(), {(+s), (-s), (-s), 1, 1});
  vertices.insert(vertices.end(), {(-s), (-s), (-s), 0, 1});
  
  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;

  v_mesh.vertices_set(vertices);
  v_mesh.indices_set(indices);

  v_mesh.buffers_generate();
  v_mesh.vertex_attributes_bind(false, true);
  
  if(pshader!=NULL){
    v_mesh.shader_set(pshader);
  }else{
    std::cerr << "err:voxel-mesh_form-shader-null" << std::endl;
  }

  if(ptexture!=NULL){
    v_mesh.texture_set(ptexture);
  }else{
    std::cerr << "err:voxel-mesh_form-shader-null" << std::endl;
  }
  
  v_mesh.position_set({x*v_size, y*v_size, z*v_size});
  v_mesh.model_matrix_form();
}

float voxel::size_get()
{
  return v_size;
}

mesh_3d* voxel::mesh_get()
{
  return &v_mesh;
}
