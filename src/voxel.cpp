#include "libs.h"
#include "mathlib.h"
#include "shader.h"
#include "textures.h"
#include "mesh.h"
#include "render.h"
#include "voxel.h"

int voxel::DEFAULT_TEXTURE_RESOLUTION=32;
int voxel::DEFAULT_TEXTURE_CHANNELS=4;
int chunk::DEFAULT_CHUNK_SIZE=16;

voxel::voxel():
  v_size(1),
  v_position({0, 0, 0}),
  v_type(VOX_NONE){
  
}

voxel::voxel(float psize, voxcoord pposition, voxtype ptype):
  v_size(psize),
  v_position(pposition),
  v_type(ptype){

}

void voxel::position_set(voxcoord pposition)
{
  v_position=pposition;
}

void voxel::size_set(float s)
{
  v_size=s;
}

void voxel::type_set(voxtype ptype)
{
  v_type=ptype;
}

mesh_3d voxel::mesh_form(shader* pshader, texture* ptexture)
{
  mesh_3d v_mesh;
  
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  float s=v_size/2;

  float x=v_position.x;
  float y=v_position.y;
  float z=v_position.z;

  int face=0;

  vertices.insert(vertices.end(), {(+s), (-s), (+s), 0, 0});
  vertices.insert(vertices.end(), {(-s), (-s), (+s), 1, 0});
  vertices.insert(vertices.end(), {(-s), (+s), (+s), 1, 1});
  vertices.insert(vertices.end(), {(+s), (+s), (+s), 0, 1});
  
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
  
  vertices.insert(vertices.end(), {(-s), (+s), (-s), 0, 0});
  vertices.insert(vertices.end(), {(+s), (+s), (-s), 1, 0});
  vertices.insert(vertices.end(), {(+s), (+s), (+s), 1, 1});
  vertices.insert(vertices.end(), {(-s), (+s), (+s), 0, 1});

  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
  
  vertices.insert(vertices.end(), {(+s), (-s), (-s), 0, 0});
  vertices.insert(vertices.end(), {(-s), (-s), (-s), 1, 0});
  vertices.insert(vertices.end(), {(-s), (-s), (+s), 1, 1});
  vertices.insert(vertices.end(), {(+s), (-s), (+s), 0, 1});
  
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

  return v_mesh;
}

mesh_3d voxel::mesh_form(bool face_top, bool face_bottom, bool face_front, bool face_back, bool face_left, bool face_right)
{
  mesh_3d v_mesh;
  
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  float s=v_size/2;

  float x=v_position.x*v_size;
  float y=v_position.y*v_size;
  float z=v_position.z*v_size;

  int face=0;

  if(face_front){
    vertices.insert(vertices.end(), {(x+s), (y-s), (z+s), 0, 0});
    vertices.insert(vertices.end(), {(x-s), (y-s), (z+s), 1, 0});
    vertices.insert(vertices.end(), {(x-s), (y+s), (z+s), 1, 1});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z+s), 0, 1});
    
    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }

  if(face_back){
    vertices.insert(vertices.end(), {(x-s), (y-s), (z-s), 0, 0});
    vertices.insert(vertices.end(), {(x+s), (y-s), (z-s), 1, 0});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z-s), 1, 1});
    vertices.insert(vertices.end(), {(x-s), (y+s), (z-s), 0, 1});

    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }

  if(face_left){
    vertices.insert(vertices.end(), {(x+s), (y-s), (z-s), 0, 0});
    vertices.insert(vertices.end(), {(x+s), (y-s), (z+s), 1, 0});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z+s), 1, 1});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z-s), 0, 1});

    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }

  if(face_right){
    vertices.insert(vertices.end(), {(x-s), (y+s), (z-s), 1, 1});
    vertices.insert(vertices.end(), {(x-s), (y+s), (z+s), 0, 1});
    vertices.insert(vertices.end(), {(x-s), (y-s), (z+s), 0, 0});
    vertices.insert(vertices.end(), {(x-s), (y-s), (z-s), 1, 0});
    
    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }

  if(face_top){
    vertices.insert(vertices.end(), {(x-s), (y+s), (z-s), 0, 0});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z-s), 1, 0});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z+s), 1, 1});
    vertices.insert(vertices.end(), {(x-s), (y+s), (z+s), 0, 1});

    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }

  if(face_bottom){
    vertices.insert(vertices.end(), {(x+s), (y-s), (z-s), 0, 0});
    vertices.insert(vertices.end(), {(x-s), (y-s), (z-s), 1, 0});
    vertices.insert(vertices.end(), {(x-s), (y-s), (z+s), 1, 1});
    vertices.insert(vertices.end(), {(x+s), (y-s), (z+s), 0, 1});
  
    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }
  
  v_mesh.vertices_set(vertices);
  v_mesh.indices_set(indices);

  v_mesh.buffers_generate();
  v_mesh.vertex_attributes_bind(false, true);

  v_mesh.position_set({x*v_size, y*v_size, z*v_size});
  v_mesh.model_matrix_form();

  return v_mesh;
}

voxtype voxel::type_get()
{
  return v_type;
}

float voxel::size_get()
{
  return v_size;
}

chunk::chunk()
{
  for(int x=0; x<DEFAULT_CHUNK_SIZE; x++){
    for(int y=0; y<DEFAULT_CHUNK_SIZE; y++){
      for(int z=0; z<DEFAULT_CHUNK_SIZE; z++){
	c_data[x][y][z].size_set(0.25);
	c_data[x][y][z].position_set({x, y, z});
	c_data[x][y][z].type_set(VOX_GRASS);
      }
    }
  }
}

chunk::chunk(voxcoord pposition, texture* ptexpack[4], shader* pshader):
  c_position(pposition){
  for(int x=0; x<3; x++){
    texture_pack[x]=ptexpack[x];
  }

  for(int x=0; x<DEFAULT_CHUNK_SIZE; x++){
    for(int y=0; y<DEFAULT_CHUNK_SIZE; y++){
      for(int z=0; z<DEFAULT_CHUNK_SIZE; z++){
	c_data[x][y][z].size_set(0.25);
	c_data[x][y][z].position_set({x, y, z});
	c_data[x][y][z].type_set(VOX_GRASS);
      }
    }
  }

  texture_pack[VOX_NONE]=NULL;
  shader_set(pshader);
}


void chunk::shader_set(shader* pshader)
{
  if(pshader!=NULL){
    c_shader=pshader;
  }else{
    std::cerr << "err:w-chunk-shader-null" << std::endl;
  }
}
void chunk::position_set(voxcoord pposition)
{
  c_position=pposition;
}

void chunk::voxel_type_set(int x, int y, int z, voxtype ptype)
{
  c_data[x][y][z].type_set(ptype);
}

voxel* chunk::voxel_get(int x, int y, int z)
{
  return &(c_data[x][y][z]);
}

mesh_3d chunk::mesh_form()
{
  mesh_3d c_mesh;

  int c;
  mesh_3d c_data_mesh[DEFAULT_CHUNK_SIZE][DEFAULT_CHUNK_SIZE][DEFAULT_CHUNK_SIZE];
  for(int x=0; x<DEFAULT_CHUNK_SIZE; x++){
    for(int y=0; y<DEFAULT_CHUNK_SIZE; y++){
      for(int z=0; z<DEFAULT_CHUNK_SIZE; z++){
	bool covered_top=true;
	bool covered_bottom=true;

	bool covered_left=true;
	bool covered_right=true;

	bool covered_front=true;
	bool covered_back=true;

	bool edge_top=false;
	bool edge_bottom=false;

	bool edge_left=false;
	bool edge_right=false;
	
	bool edge_front=false;
	bool edge_back=false;
	
	if(y!=0 && y<DEFAULT_CHUNK_SIZE-1){
	  covered_top=c_data[x][++y][z].type_get()!=VOX_NONE;
	  covered_bottom=c_data[x][--y][z].type_get()!=VOX_NONE;
	}else{
	  if(y==0){edge_bottom=true;}
	  if(y==DEFAULT_CHUNK_SIZE-1){edge_top=true;}
	}

	if(x!=0 && x<DEFAULT_CHUNK_SIZE-1){
	  covered_right=c_data[--x][y][z].type_get()!=VOX_NONE;
	  covered_left=c_data[++x][y][z].type_get()!=VOX_NONE;
	}else{
	  if(x==0){edge_right=true;}
	  if(x==DEFAULT_CHUNK_SIZE-1){edge_left=true;}
	}

	if(z!=0 && z<DEFAULT_CHUNK_SIZE-1){
	  covered_front=c_data[x][y][++z].type_get()!=VOX_NONE;
	  covered_back=c_data[x][y][--z].type_get()!=VOX_NONE;
	}else{
	  if(z==0){edge_back=true;}
	  if(z==DEFAULT_CHUNK_SIZE-1){edge_front=true;}
	}

	bool face_top=(!covered_top || edge_top);
	bool face_bottom=(!covered_bottom || edge_bottom);

	bool face_right=(!covered_right || edge_right);
	bool face_left=(!covered_left || edge_left);

	bool face_front=(!covered_front || edge_front);
	bool face_back=(!covered_back || edge_back);
	
	if(c_data[x][y][z].type_get()!=VOX_NONE){
	  c_data_mesh[x][y][z]=c_data[x][y][z].mesh_form(face_top, face_bottom, face_front, face_back, face_left, face_right);
	}
	
	std::vector<float> mesh_verts=c_mesh.vertices_get();
	std::vector<unsigned int> mesh_inds=c_mesh.indices_get();

	std::vector<float> new_verts=c_data_mesh[x][y][z].vertices_get();
	std::vector<unsigned int> new_inds=c_data_mesh[x][y][z].indices_get();
	for(int x=0; x<new_inds.size(); x++){
	  new_inds[x]+=c*4;
	}
	
	std::vector<float> cat;
	cat.insert(cat.end(), mesh_verts.begin(), mesh_verts.end());
	cat.insert(cat.end(), new_verts.begin(), new_verts.end());

	std::vector<unsigned int> catind;
	catind.insert(catind.end(), mesh_inds.begin(), mesh_inds.end());
	catind.insert(catind.end(), new_inds.begin(), new_inds.end());
	
	c_mesh.vertices_set(cat);
	c_mesh.indices_set(catind);

	if(c_data[x][y][z].type_get()!=VOX_NONE){
	  c+=face_top+face_bottom+face_left+face_right+face_front+face_back;
	}
      }
    }
  }

  c_mesh.buffers_generate();
  c_mesh.vertex_attributes_bind(false, true);
  
  if(texture_pack[VOX_GRASS]!=NULL){
    c_mesh.texture_set(texture_pack[VOX_GRASS]);
  }else{
    std::cerr << "err:w-chunk-mesh_form-texture_pack-element-null" << std::endl;
  }

  if(c_shader){
    c_mesh.shader_set(c_shader);
  }else{
    std::cerr << "err:w-chunk-mesh_form-c_shader-null" << std::endl;
  }

  vector_3d pos(c_position.x*DEFAULT_CHUNK_SIZE, c_position.y*DEFAULT_CHUNK_SIZE, c_position.z*DEFAULT_CHUNK_SIZE);
  
  c_mesh.position_set(pos);
  c_mesh.model_matrix_form();

  return c_mesh;
}

shader* chunk::shader_get()
{
  return c_shader;
}
