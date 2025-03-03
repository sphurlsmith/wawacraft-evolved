#include "libs.h"
#include "mathlib.h"
#include "shader.h"
#include "textures.h"
#include "mesh.h"
#include "render.h"
#include "voxel.h"

int voxel::DEFAULT_TEXTURE_RESOLUTION=32;
int voxel::DEFAULT_TEXTURE_CHANNELS=4;

float voxel::DEFAULT_SHADE_DARKEST=0.4;
float voxel::DEFAULT_SHADE_MIDDLE=0.8;
float voxel::DEFAULT_SHADE_LIGHTEST=1;

const int chunk::DEFAULT_CHUNK_SIZE;
const int chunk::DEFAULT_CHUNK_AREA;

int chunk::DEFAULT_TEXTUREPACK_RESOLUTION=512;
int chunk::DEFAULT_TEXTUREPACK_CAPACITY=16;

const int chunk_manager::DEFAULT_VISIBLE_RADIUS=4;
const int chunk_manager::DEFAULT_VISIBLE_AREA=(1+2*DEFAULT_VISIBLE_RADIUS)*(1+2*DEFAULT_VISIBLE_RADIUS);

const float chunk_manager::DEFAULT_RAYCAST_RADIUS=5;

int chunk_manager::DEFAULT_BLOCK_OPS_PER_FRAME=1;

float chunk::DEFAULT_BLOCK_SCALE=0.25;

bool operator==(const voxcoord& a, const voxcoord& b)
{
  if(a.x==b.x && a.y==b.y && a.z==b.z){
    return true;
  }else{
    return false;
  }
}

bool operator!=(const voxcoord& a, const voxcoord& b){
  if(!(a==b)){
    return true;
  }else{
    return false;
  }
}

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

static int voxel::index_get(int x, int y, int z, int width, int height){
  return (x+(y*width)+(z*width*height));
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

  vertices.insert(vertices.end(), {(+s), (-s), (+s), 0, 0, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(-s), (-s), (+s), 1, 0, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(-s), (+s), (+s), 1, 1, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(+s), (+s), (+s), 0, 1, DEFAULT_SHADE_MIDDLE});
  
  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
    
  vertices.insert(vertices.end(), {(-s), (-s), (-s), 0, 0, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(+s), (-s), (-s), 1, 0, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(+s), (+s), (-s), 1, 1, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(-s), (+s), (-s), 0, 1, DEFAULT_SHADE_MIDDLE});

  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
  
  vertices.insert(vertices.end(), {(+s), (-s), (-s), 0, 0, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(+s), (-s), (+s), 1, 0, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(+s), (+s), (+s), 1, 1, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(+s), (+s), (-s), 0, 1, DEFAULT_SHADE_MIDDLE});

  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
  
  vertices.insert(vertices.end(), {(-s), (+s), (-s), 1, 1, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(-s), (+s), (+s), 0, 1, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(-s), (-s), (+s), 0, 0, DEFAULT_SHADE_MIDDLE});
  vertices.insert(vertices.end(), {(-s), (-s), (-s), 1, 0, DEFAULT_SHADE_MIDDLE});

  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
  
  vertices.insert(vertices.end(), {(-s), (+s), (-s), 0, 0, DEFAULT_SHADE_LIGHTEST});
  vertices.insert(vertices.end(), {(+s), (+s), (-s), 1, 0, DEFAULT_SHADE_LIGHTEST});
  vertices.insert(vertices.end(), {(+s), (+s), (+s), 1, 1, DEFAULT_SHADE_LIGHTEST});
  vertices.insert(vertices.end(), {(-s), (+s), (+s), 0, 1, DEFAULT_SHADE_LIGHTEST});

  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;
  
  vertices.insert(vertices.end(), {(+s), (-s), (-s), 0, 0, DEFAULT_SHADE_DARKEST});
  vertices.insert(vertices.end(), {(-s), (-s), (-s), 1, 0, DEFAULT_SHADE_DARKEST});
  vertices.insert(vertices.end(), {(-s), (-s), (+s), 1, 1, DEFAULT_SHADE_DARKEST});
  vertices.insert(vertices.end(), {(+s), (-s), (+s), 0, 1, DEFAULT_SHADE_DARKEST});
  
  indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
  face+=4;

  v_mesh.vertices_set(vertices);
  v_mesh.indices_set(indices);

  v_mesh.buffers_generate();
  v_mesh.vertex_attributes_bind(false, true, true);
  
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

static std::vector<float> voxel::vertices_form(voxcoord v_position, float v_size, spritecoord psc, bool face_top, bool face_bottom, bool face_front, bool face_back, bool face_left, bool face_right)
{
  std::vector<float> vertices;
  
  float s=v_size/2;

  float x=v_position.x*v_size;
  float y=v_position.y*v_size;
  float z=v_position.z*v_size;

  if(face_front){
    vertices.insert(vertices.end(), {(x+s), (y-s), (z+s), psc.x0, psc.y0, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x-s), (y-s), (z+s), psc.x1, psc.y0, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x-s), (y+s), (z+s), psc.x1, psc.y1, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z+s), psc.x0, psc.y1, DEFAULT_SHADE_MIDDLE});
  }

  if(face_back){
    vertices.insert(vertices.end(), {(x-s), (y-s), (z-s), psc.x0, psc.y0, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x+s), (y-s), (z-s), psc.x1, psc.y0, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z-s), psc.x1, psc.y1, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x-s), (y+s), (z-s), psc.x0, psc.y1, DEFAULT_SHADE_MIDDLE});
  }

  if(face_left){
    vertices.insert(vertices.end(), {(x-s), (y+s), (z-s), psc.x1, psc.y1, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x-s), (y+s), (z+s), psc.x0, psc.y1, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x-s), (y-s), (z+s), psc.x0, psc.y0, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x-s), (y-s), (z-s), psc.x1, psc.y0, DEFAULT_SHADE_MIDDLE});
  }
  
  if(face_right){
    vertices.insert(vertices.end(), {(x+s), (y-s), (z-s), psc.x0, psc.y0, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x+s), (y-s), (z+s), psc.x1, psc.y0, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z+s), psc.x1, psc.y1, DEFAULT_SHADE_MIDDLE});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z-s), psc.x0, psc.y1, DEFAULT_SHADE_MIDDLE});
  }

  if(face_top){
    vertices.insert(vertices.end(), {(x-s), (y+s), (z-s), psc.x0, psc.y0, DEFAULT_SHADE_LIGHTEST});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z-s), psc.x1, psc.y0, DEFAULT_SHADE_LIGHTEST});
    vertices.insert(vertices.end(), {(x+s), (y+s), (z+s), psc.x1, psc.y1, DEFAULT_SHADE_LIGHTEST});
    vertices.insert(vertices.end(), {(x-s), (y+s), (z+s), psc.x0, psc.y1, DEFAULT_SHADE_LIGHTEST});
  }

  if(face_bottom){
    vertices.insert(vertices.end(), {(x+s), (y-s), (z-s), psc.x0, psc.y0, DEFAULT_SHADE_DARKEST});
    vertices.insert(vertices.end(), {(x-s), (y-s), (z-s), psc.x1, psc.y0, DEFAULT_SHADE_DARKEST});
    vertices.insert(vertices.end(), {(x-s), (y-s), (z+s), psc.x1, psc.y1, DEFAULT_SHADE_DARKEST});
    vertices.insert(vertices.end(), {(x+s), (y-s), (z+s), psc.x0, psc.y1, DEFAULT_SHADE_DARKEST});
  }
  
  return vertices;
}

static std::vector<unsigned int> voxel::indices_form(bool face_top, bool face_bottom, bool face_front, bool face_back, bool face_left, bool face_right)
{
  std::vector<unsigned int> indices;

  int face=0;

  if(face_front){
    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }

  if(face_back){
    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }

  if(face_left){
    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }
  
  if(face_right){
    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }

  if(face_top){
    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }

  if(face_bottom){
    indices.insert(indices.end(), {0+face, 1+face, 2+face, 2+face, 3+face, 0+face});
    face+=4;
  }
  
  return indices;
}

voxcoord voxel::position_get()
{
  return v_position;
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
  c_mesh.buffers_generate();
  
  for(int x=0; x<DEFAULT_CHUNK_SIZE*DEFAULT_CHUNK_SIZE*DEFAULT_CHUNK_SIZE; x++){
    c_data[x]=VOX_NONE;
  }
}

chunk::chunk(voxcoord pposition, texture* pspritesheet, shader* pshader):
  c_position(pposition){
  for(int x=0; x<DEFAULT_CHUNK_SIZE*DEFAULT_CHUNK_SIZE*DEFAULT_CHUNK_SIZE; x++){
    c_data[x]=VOX_NONE;
  }

  c_mesh.buffers_generate();

  spritesheet=pspritesheet;
  shader_set(pshader);
}

static spritecoord chunk::voxel_sprite_location_get(voxtype pv)
{
  spritecoord ret;
  
  int x=pv%DEFAULT_CHUNK_SIZE;
  int y=pv/DEFAULT_CHUNK_SIZE;
  
  ret.x0=float(x)/DEFAULT_TEXTUREPACK_CAPACITY;
  ret.x1=float(x+1)/DEFAULT_TEXTUREPACK_CAPACITY;

  ret.y0=1-float(y+1)/DEFAULT_TEXTUREPACK_CAPACITY;
  ret.y1=1-float(y)/DEFAULT_TEXTUREPACK_CAPACITY;

  return ret;
}

static void chunk::terrain_flat(chunk& pchunk, int stone_height, int soil_height, int grass_height)
{
  for(int x=0; x<chunk::DEFAULT_CHUNK_SIZE; x++){
    for(int y=0; y<chunk::DEFAULT_CHUNK_SIZE; y++){
      for(int z=0; z<chunk::DEFAULT_CHUNK_SIZE; z++){
	if(y<=grass_height){
	  if(y<=stone_height){
	    pchunk.voxel_set(x, y, z, VOX_STONE);
	  }else if(y<=soil_height){
	    pchunk.voxel_set(x, y, z, VOX_SOIL);
	  }else{
	    pchunk.voxel_set(x, y, z, VOX_GRASS);
	  }
	}else{
	  pchunk.voxel_set(x, y, z, VOX_NONE);
	}
      }
    }
  }
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

void chunk::voxel_set(int x, int y, int z, voxtype ptype)
{
  c_data[voxel::index_get(x, y, z, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)]=ptype;
}

voxel chunk::voxel_get(int x, int y, int z)
{
  voxel ret;

  ret.size_set(DEFAULT_BLOCK_SCALE);
  ret.position_set({x, y, z});
  ret.type_set(c_data[voxel::index_get(x, y, z, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)]);

  return ret;
}

voxcoord chunk::voxel_raycast(vector_3d initial_position, vector_3d target, bool current_or_previous=true)
{
  float x=initial_position.x;
  float y=initial_position.y;
  float z=initial_position.z;

  float px=x;
  float py=y;
  float pz=z;
  
  float fx=0;
  float fy=0;
  float fz=0;
  
  float tx=target.x;
  float ty=target.y;
  float tz=target.z;
  
  float sx=(tx>0) ? 1 : -1;
  float sy=(ty>0) ? 1 : -1;
  float sz=(tz>0) ? 1 : -1;
  
  float dx=sx/tx;
  float dy=sy/ty;
  float dz=sz/tz;
  
  float ax=((floor(x)+sx)-x)/tx;
  float ay=((floor(y)+sy)-y)/ty;
  float az=((floor(z)+sz)-z)/tz;
  
  while(x<=DEFAULT_CHUNK_SIZE && y<=DEFAULT_CHUNK_SIZE && z<=DEFAULT_CHUNK_SIZE &&
	x>=-1 && y>=-1 && z>=-1){
    if(c_data[voxel::index_get(x, y, z, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)]!=VOX_NONE && x<DEFAULT_CHUNK_SIZE && y<DEFAULT_CHUNK_SIZE && z<DEFAULT_CHUNK_SIZE &&	x>=0 && y>=0 && z>=0){
      break;
    }
    
    if(ax<ay){
      if(ax<az){
	x+=sx;
	ax+=dx;

	fx=-sx;
	fy=0;
	fz=0;
      }else{
	z+=sz;
	az+=dz;

	fx=0;
	fy=0;
	fz=-sz;
      }
    }else{
      if(ay<az){
	y+=sy;
	ay+=dy;

	fx=0;
	fy=-sy;
	fz=0;
      }else{
	z+=sz;
	az+=dz;

	fx=0;
	fy=0;
	fz=-sz;
      }
    }
  }

  if(!current_or_previous){
    return{fx, fy, fz};
  }
  
  return {x, y, z};
}

void chunk::mesh_form()
{
  int c=0;

  std::vector<float> mesh_verts;
  std::vector<unsigned int> mesh_inds;

  std::vector<float> new_verts;
  std::vector<unsigned int> new_inds;
  
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

	voxtype here=c_data[voxel::index_get(x, y, z, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)];
	
	if(y>=0 && y<=DEFAULT_CHUNK_SIZE-1){
	  voxtype top=c_data[voxel::index_get(x, y+1, z, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)];
	  voxtype bottom=c_data[voxel::index_get(x, y-1, z, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)];
	  
	  covered_top=!((top==VOX_NONE) || (top==VOX_WAWA && here!=VOX_WAWA) || (top==VOX_UNI && here!=VOX_UNI));
	  covered_bottom=!((bottom==VOX_NONE) || (bottom==VOX_WAWA && here!=VOX_WAWA) || (bottom==VOX_UNI && here!=VOX_UNI));
	}
	
	if(y==0){edge_bottom=true;}
	if(y==DEFAULT_CHUNK_SIZE-1){edge_top=true;}
	
	if(x>=0 && x<=DEFAULT_CHUNK_SIZE-1){
	  voxtype left=c_data[voxel::index_get(x-1, y, z, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)];
	  voxtype right=c_data[voxel::index_get(x+1, y, z, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)];

	  covered_left=!((left==VOX_NONE) || (left==VOX_WAWA && here!=VOX_WAWA) || (left==VOX_UNI && here!=VOX_UNI));
	  covered_right=!((right==VOX_NONE) || (right==VOX_WAWA && here!=VOX_WAWA) || (right==VOX_UNI && here!=VOX_UNI));
	}
	
	if(x==0){edge_left=true;}
	if(x==DEFAULT_CHUNK_SIZE-1){edge_right=true;}
	
	if(z>=0 && z<=DEFAULT_CHUNK_SIZE-1){
	  voxtype front=c_data[voxel::index_get(x, y, z+1, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)];
	  voxtype back=c_data[voxel::index_get(x, y, z-1, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)];

	  covered_front=!((front==VOX_NONE) || (front==VOX_WAWA && here!=VOX_WAWA) || (front==VOX_UNI && here!=VOX_UNI));
	  covered_back=!((back==VOX_NONE) || (back==VOX_WAWA && here!=VOX_WAWA) || (back==VOX_UNI && here!=VOX_UNI));
	}
	
	if(z==0){edge_back=true;}
	if(z==DEFAULT_CHUNK_SIZE-1){edge_front=true;}
        
	bool face_top=(!covered_top || edge_top);
	bool face_bottom=(!covered_bottom || edge_bottom);

	bool face_right=(!covered_right || edge_right);
	bool face_left=(!covered_left || edge_left);

	bool face_front=(!covered_front || edge_front);
	bool face_back=(!covered_back || edge_back);
	
	if(c_data[voxel::index_get(x, y, z, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)]!=VOX_NONE){
	  spritecoord vsp=chunk::voxel_sprite_location_get(c_data[voxel::index_get(x, y, z, DEFAULT_CHUNK_SIZE, DEFAULT_CHUNK_SIZE)]);
	  
	  new_verts=voxel::vertices_form({x, y, z}, DEFAULT_BLOCK_SCALE, vsp,face_top, face_bottom, face_front, face_back, face_left, face_right);
	  new_inds=voxel::indices_form(face_top, face_bottom, face_front, face_back, face_left, face_right);

	  for(int x=0; x<new_inds.size(); x++){
	    new_inds[x]+=c*4;
	  }
	  
	  mesh_verts.insert(mesh_verts.end(), new_verts.begin(), new_verts.end());
	  mesh_inds.insert(mesh_inds.end(), new_inds.begin(), new_inds.end());
	  
	  if(face_top){c++;}
	  if(face_bottom){c++;}
	  if(face_front){c++;}
	  if(face_back){c++;}
	  if(face_left){c++;}
	  if(face_right){c++;}
	}
      }
    }
  }
  
  c_mesh.vertices_set(mesh_verts);
  c_mesh.indices_set(mesh_inds);
    
  if(spritesheet!=NULL){
    c_mesh.texture_set(spritesheet);
  }else{
    std::cerr << "err:w-chunk-mesh_form-spritesheet-null" << std::endl;
  }

  if(c_shader){
    c_mesh.shader_set(c_shader);
  }else{
    std::cerr << "err:w-chunk-mesh_form-c_shader-null" << std::endl;
  }

  c_mesh.vertex_attributes_bind(false, true, true);
  
  vector_3d pos(c_position.x*DEFAULT_CHUNK_SIZE*DEFAULT_BLOCK_SCALE, c_position.y*DEFAULT_CHUNK_SIZE*DEFAULT_BLOCK_SCALE, c_position.z*DEFAULT_CHUNK_SIZE*DEFAULT_BLOCK_SCALE);

  c_mesh.position_set(pos);
  c_mesh.model_matrix_form();
}

voxcoord chunk::position_get()
{
  return c_position;
}

mesh_3d* chunk::mesh_get()
{
  return &c_mesh;
}

shader* chunk::shader_get()
{
  return c_shader;
}

chunk_manager::chunk_manager(texture* pspritesheet, shader* pshader):
  default_spritesheet(pspritesheet),
  default_shader(pshader),
  block_operations_total(0){
  
}

void chunk_manager::chunk_group_setup()
{
  if(default_spritesheet==NULL){
    std::cerr << "err-chunk_manager-chunk_group_setup-spritesheet-null" << std::endl;
  }

  if(default_shader==NULL){
    std::cerr << "err-chunk_manager-chunk_group_setup-shader-null" << std::endl;
  }
  
  for(int x=0; x<cm_data.size(); x++){
    if(!cm_data[x].setup){
      int h_stone=rand()%2+1;
      int h_soil=h_stone+(rand()%2+1);
      int h_grass=h_soil+1;

      cm_data[x].shader_set(default_shader);
      cm_data[x].spritesheet=default_spritesheet;

      chunk::terrain_flat(cm_data[x], h_stone, h_soil, h_grass);
      cm_data[x].setup=true;
    }
  }

  chunk_group_build();
}

void chunk_manager::chunk_group_build()
{
  for(int x=0; x<cm_data.size(); x++){
    if(!cm_data[x].built){
      cm_data[x].mesh_form();
      cm_data[x].built=true;
    }
  }
}

void chunk_manager::update(vector_3d camera_position)
{
  chunk_group_setup();
  chunk_group_build();
  chunk_group_visible(camera_position);
}

void chunk_manager::chunk_group_visible(vector_3d camera_position)
{
  cm_visible.clear();

  float conversion=chunk::DEFAULT_CHUNK_SIZE*chunk::DEFAULT_BLOCK_SCALE;
  
  int x_location=camera_position.x/conversion;
  int z_location=camera_position.z/conversion;
  
  int x_bound_lesser=x_location-DEFAULT_VISIBLE_RADIUS;
  int x_bound_higher=x_location+DEFAULT_VISIBLE_RADIUS;
  
  int z_bound_lesser=z_location-DEFAULT_VISIBLE_RADIUS;
  int z_bound_higher=z_location+DEFAULT_VISIBLE_RADIUS;

  for(int x=0; x<cm_data.size(); x++){
    for(int i=0; i<cm_visible.size(); i++){
      if(cm_visible[i]!=x){
	if(i==cm_visible.size()-1){
	  chunk_unload(x);
	}
      }
    }
  }
  
  for(int x=x_bound_lesser; x<=x_bound_higher; x++){
    for(int z=z_bound_lesser; z<=z_bound_higher; z++){
      if(!chunk_exists({x, 0, z})){
	chunk_init({x, 0, z});
      }

      chunk_setup({x, 0, z});
      chunk_build({x, 0, z});
      
      cm_visible.push_back(chunk_search({x, 0, z}));
    }
  }
}

void chunk_manager::chunk_setup(voxcoord pos){
  if(default_spritesheet==NULL){
    std::cerr << "err-chunk_manager-chunk_setup-spritesheet-null" << std::endl;
  }

  if(default_shader==NULL){
    std::cerr << "err-chunk_manager-chunk_setup-shader-null" << std::endl;
  }

  int i=chunk_search(pos);
  
  if(chunk_exists(pos) && !cm_data[i].setup){
    int h_stone=rand()%5+1;
    int h_soil=h_stone+(rand()%3+1);
    int h_grass=h_soil+1;

    cm_data[i].shader_set(default_shader);
    cm_data[i].spritesheet=default_spritesheet;

    chunk::terrain_flat(cm_data[i], h_stone, h_soil, h_grass);
    cm_data[i].setup=true;
  }
}

void chunk_manager::chunk_build(voxcoord pos){
  if(chunk_exists(pos) && !cm_data[chunk_search(pos)].built){
    cm_data[chunk_search(pos)].mesh_form();
    cm_data[chunk_search(pos)].built=true;
  }
}

void chunk_manager::chunk_unload(int index)
{
  if(index<cm_data.size()){
    cm_data[index].c_mesh.vertices_set({0});
    cm_data[index].c_mesh.indices_set({0});
    cm_data[index].built=false;
  }
}

void chunk_manager::chunk_unload(voxcoord pos)
{
  if(chunk_exists(pos)){
    cm_data[chunk_search(pos)].c_mesh.vertices_set({0});
    cm_data[chunk_search(pos)].c_mesh.indices_set({0});
    cm_data[chunk_search(pos)].built=false;
  }
}

bool chunk_manager::chunk_init(voxcoord pos)
{
  bool allowed=!(chunk_exists(pos));

  if(allowed){
    chunk c_new;
    c_new.position_set(pos);
    cm_data.push_back(c_new);
    return true;
  }

  return false;
}

bool chunk_manager::chunk_delete(voxcoord pos)
{
  if(chunk_exists(pos)){
    cm_data.erase(cm_data.begin()+chunk_search(pos));
    return true;
  }

  return false;
}

bool chunk_manager::chunk_exists(voxcoord ppos)
{
  for(int x=0; x<cm_data.size(); x++){
    if(cm_data[x].position_get()==ppos){
      return true;
    }
  }

  return false;
}

bool chunk_manager::block_break(vector_3d initial_position, vector_3d target){
  int cx=(initial_position.x/chunk::DEFAULT_BLOCK_SCALE)/chunk::DEFAULT_CHUNK_SIZE;
  int cy=(initial_position.y/chunk::DEFAULT_BLOCK_SCALE)/chunk::DEFAULT_CHUNK_SIZE;
  int cz=(initial_position.z/chunk::DEFAULT_BLOCK_SCALE)/chunk::DEFAULT_CHUNK_SIZE;

  float ix=fmod((initial_position.x/chunk::DEFAULT_BLOCK_SCALE), chunk::DEFAULT_CHUNK_SIZE);
  float iy=fmod((initial_position.y/chunk::DEFAULT_BLOCK_SCALE), chunk::DEFAULT_CHUNK_SIZE);
  float iz=fmod((initial_position.z/chunk::DEFAULT_BLOCK_SCALE), chunk::DEFAULT_CHUNK_SIZE);

  if(ix<0){ix+=chunk::DEFAULT_CHUNK_SIZE;cx--;}
  if(iy<0){iy+=chunk::DEFAULT_CHUNK_SIZE;cy--;}
  if(iz<0){iz+=chunk::DEFAULT_CHUNK_SIZE;cz--;}
    
  vector_3d converted_initial(ix, iy, iz);
  
  if(chunk_exists({cx, cy, cz})){
    voxcoord hit=cm_data[chunk_search({cx, cy, cz})].voxel_raycast(converted_initial, target);
    
    while(hit.x<0){hit.x+=chunk::DEFAULT_CHUNK_SIZE;cx--;}
    while(hit.y<0){hit.y+=chunk::DEFAULT_CHUNK_SIZE;cy--;}
    while(hit.z<0){hit.z+=chunk::DEFAULT_CHUNK_SIZE;cz--;}

    while(hit.x>=chunk::DEFAULT_CHUNK_SIZE){hit.x-=chunk::DEFAULT_CHUNK_SIZE;cx++;}
    while(hit.y>=chunk::DEFAULT_CHUNK_SIZE){hit.y-=chunk::DEFAULT_CHUNK_SIZE;cy++;}
    while(hit.z>=chunk::DEFAULT_CHUNK_SIZE){hit.z-=chunk::DEFAULT_CHUNK_SIZE;cz++;}
    
    hit=cm_data[chunk_search({cx, cy, cz})].voxel_raycast(vector_3d(hit.x, hit.y, hit.z), target);
    
    if(chunk_exists({cx, cy, cz}) && block_operations_total<DEFAULT_BLOCK_OPS_PER_FRAME){
      cm_data[chunk_search({cx, cy, cz})].voxel_set(hit.x, hit.y, hit.z, VOX_NONE);
      cm_data[chunk_search({cx, cy, cz})].built=false;

      block_operations_total++;
      return true;
    }
  }else{
    std::cerr << "err:chunk_manager-block_break-chunk-null-at-pos" << std::endl;
  }

  return false;
}

bool chunk_manager::block_place(vector_3d initial_position, vector_3d target, voxtype type){
  int cx=(initial_position.x/chunk::DEFAULT_BLOCK_SCALE)/chunk::DEFAULT_CHUNK_SIZE;
  int cy=(initial_position.y/chunk::DEFAULT_BLOCK_SCALE)/chunk::DEFAULT_CHUNK_SIZE;
  int cz=(initial_position.z/chunk::DEFAULT_BLOCK_SCALE)/chunk::DEFAULT_CHUNK_SIZE;
  
  int pcx=cx;
  int pcy=cy;
  int pcz=cz;
  
  float ix=fmod((initial_position.x/chunk::DEFAULT_BLOCK_SCALE), chunk::DEFAULT_CHUNK_SIZE);
  float iy=fmod((initial_position.y/chunk::DEFAULT_BLOCK_SCALE), chunk::DEFAULT_CHUNK_SIZE);
  float iz=fmod((initial_position.z/chunk::DEFAULT_BLOCK_SCALE), chunk::DEFAULT_CHUNK_SIZE);

  if(ix<0){ix+=chunk::DEFAULT_CHUNK_SIZE;cx--;}
  if(iy<0){iy+=chunk::DEFAULT_CHUNK_SIZE;cy--;}
  if(iz<0){iz+=chunk::DEFAULT_CHUNK_SIZE;cz--;}
    
  vector_3d converted_initial(ix, iy, iz);
  
  if(chunk_exists({cx, cy, cz})){
    voxcoord face=cm_data[chunk_search({cx, cy, cz})].voxel_raycast(converted_initial, target, false);
    voxcoord hit=cm_data[chunk_search({cx, cy, cz})].voxel_raycast(converted_initial, target);
    
    if(hit.x<=-1 || hit.y<=-1 || hit.z<=-1 ||
       hit.x>=chunk::DEFAULT_CHUNK_SIZE ||
       hit.y>=chunk::DEFAULT_CHUNK_SIZE ||
       hit.z>=chunk::DEFAULT_CHUNK_SIZE ||
       cm_data[chunk_search({cx, cy, cz})].voxel_get(hit.x, hit.y, hit.z).type_get()==VOX_NONE){
      while(hit.x<0){hit.x+=chunk::DEFAULT_CHUNK_SIZE;cx--;}
      while(hit.y<0){hit.y+=chunk::DEFAULT_CHUNK_SIZE;cy--;}
      while(hit.z<0){hit.z+=chunk::DEFAULT_CHUNK_SIZE;cz--;}
      
      while(hit.x>=chunk::DEFAULT_CHUNK_SIZE){hit.x-=chunk::DEFAULT_CHUNK_SIZE;cx++;}
      while(hit.y>=chunk::DEFAULT_CHUNK_SIZE){hit.y-=chunk::DEFAULT_CHUNK_SIZE;cy++;}
      while(hit.z>=chunk::DEFAULT_CHUNK_SIZE){hit.z-=chunk::DEFAULT_CHUNK_SIZE;cz++;}

      voxcoord newv=cm_data[chunk_search({cx, cy, cz})].voxel_raycast(vector_3d(hit.x, hit.y, hit.z), target, false);
      voxcoord err={0, 0, 0};
      
      if(newv!=err){
	face=newv;
      }
      
      hit=cm_data[chunk_search({cx, cy, cz})].voxel_raycast(vector_3d(hit.x, hit.y, hit.z), target);
    }

    hit.x+=face.x;
    hit.y+=face.y;
    hit.z+=face.z;
    
    while(hit.x<0){hit.x+=chunk::DEFAULT_CHUNK_SIZE;cx--;}
    while(hit.y<0){hit.y+=chunk::DEFAULT_CHUNK_SIZE;cy--;}
    while(hit.z<0){hit.z+=chunk::DEFAULT_CHUNK_SIZE;cz--;}
    
    while(hit.x>=chunk::DEFAULT_CHUNK_SIZE){hit.x-=chunk::DEFAULT_CHUNK_SIZE;cx++;}
    while(hit.y>=chunk::DEFAULT_CHUNK_SIZE){hit.y-=chunk::DEFAULT_CHUNK_SIZE;cy++;}
    while(hit.z>=chunk::DEFAULT_CHUNK_SIZE){hit.z-=chunk::DEFAULT_CHUNK_SIZE;cz++;}
    
    if(chunk_exists({cx, cy, cz}) && block_operations_total<DEFAULT_BLOCK_OPS_PER_FRAME){
      cm_data[chunk_search({cx, cy, cz})].voxel_set(hit.x, hit.y, hit.z, type);
      cm_data[chunk_search({cx, cy, cz})].built=false;

      block_operations_total++;
      return true;
    }
  }else{
    std::cerr << "err:chunk_manager-block_place-chunk-null-at-pos" << std::endl;
  }

  return false;
}

int chunk_manager::chunk_search(voxcoord pos)
{
  for(int x=0; x<cm_data.size(); x++){
    if(cm_data[x].position_get()==pos){
      return x;
    }
  }

  return -1;
}
