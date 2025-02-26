#ifndef VOXEL_H
#define VOXEL_H

#include "libs.h"
#include "mathlib.h"
#include "noise.h"
#include "shader.h"
#include "textures.h"
#include "mesh.h"
#include "render.h"

struct voxcoord{
  int x;
  int y;
  int z;
};

struct spritecoord{
  float x0=0;
  float x1=0;
  float y0=0;
  float y1=0;
};

enum voxtype{
  VOX_NONE,
  VOX_GRASS,
  VOX_SOIL,
  VOX_WOOD,
  VOX_STONE,
  VOX_WAWA,
  VOX_UNI
};

class voxel{
 public:
  voxel();
  voxel(float psize, voxcoord pposition, voxtype ptype);

  void position_set(voxcoord pposition);
  void size_set(float s);
  void type_set(voxtype ptype);

  static int index_get(int x, int y, int z, int width, int height);
  
  mesh_3d mesh_form(shader* pshader, texture* ptexture);

  static std::vector<float> vertices_form(voxcoord v_position, float v_size, spritecoord psc, bool face_top, bool face_bottom, bool face_front, bool face_back, bool face_left, bool face_right);
  static std::vector<unsigned int> indices_form(bool face_top, bool face_bottom, bool face_front, bool face_back, bool face_left, bool face_right);

  voxcoord position_get();
  voxtype type_get();

  float size_get();

  static int DEFAULT_TEXTURE_RESOLUTION;
  static int DEFAULT_TEXTURE_CHANNELS;

  static float DEFAULT_SHADE_DARKEST;
  static float DEFAULT_SHADE_MIDDLE;
  static float DEFAULT_SHADE_LIGHTEST;

 private:
  float v_size;

  voxcoord v_position;
  voxtype v_type;
};

class chunk{
 public:
  chunk();
  chunk(voxcoord pposition, texture* pspritesheet, shader* pshader);

  static spritecoord voxel_sprite_location_get(voxtype pv);

  static void terrain_flat(chunk& pchunk, int stone_height, int soil_height, int grass_height);
  static void terrain_perlin(chunk& pchunk);
  
  void shader_set(shader* pshader);
  void position_set(voxcoord pposition);
  void voxel_set(int x, int y, int z, voxtype ptype);

  void mesh_form();
  
  voxcoord position_get();
  
  voxel voxel_get(int x, int y, int z);
  voxcoord voxel_raycast(vector_3d initial_position, vector_3d target, bool current_or_previous=true);
  
  mesh_3d* mesh_get();

  shader* shader_get();
  texture* spritesheet;

  static const int DEFAULT_CHUNK_SIZE=16;
  static const int DEFAULT_CHUNK_AREA=DEFAULT_CHUNK_SIZE*DEFAULT_CHUNK_SIZE*DEFAULT_CHUNK_SIZE;
  
  static int DEFAULT_TEXTUREPACK_RESOLUTION;
  static int DEFAULT_TEXTUREPACK_CAPACITY;

  static float DEFAULT_BLOCK_SCALE;

 private:
  voxcoord c_position;
  voxtype c_data[DEFAULT_CHUNK_AREA];

  mesh_3d c_mesh;
  shader* c_shader;

 protected:
  bool setup=false;
  bool built=false;
  
  friend class chunk_manager;
};

class chunk_manager{
 public:
  chunk_manager(texture* pspritesheet, shader* pshader);

  void update(vector_3d camera_position);
  
  void chunk_group_setup();
  void chunk_group_build();
  void chunk_group_visible(vector_3d camera_position);

  void chunk_setup(voxcoord pos);
  void chunk_build(voxcoord pos);

  void chunk_unload(int index);
  void chunk_unload(voxcoord pos);
  
  bool chunk_init(voxcoord pos);
  bool chunk_delete(voxcoord pos);
  
  bool chunk_exists(voxcoord ppos);

  bool block_break(vector_3d initial_position, vector_3d target);
  bool block_place(vector_3d initial_position, vector_3d target, voxtype type);
  
  int chunk_search(voxcoord pos);
  
  static const int DEFAULT_VISIBLE_RADIUS;
  static const int DEFAULT_VISIBLE_AREA;

  static const float DEFAULT_RAYCAST_RADIUS;

  static int DEFAULT_BLOCK_OPS_PER_FRAME;
  
  texture* default_spritesheet;
  shader* default_shader;

  std::vector<int> cm_visible;
  std::vector<chunk> cm_data;

  int block_operations_total;
};

#endif
