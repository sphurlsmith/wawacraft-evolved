#ifndef VOXEL_H
#define VOXEL_H

#include "libs.h"
#include "mathlib.h"
#include "shader.h"
#include "textures.h"
#include "mesh.h"
#include "render.h"

struct voxcoord{
  int x;
  int y;
  int z;
};

enum voxtype{
  VOX_NONE,
  VOX_GRASS,
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
  
  mesh_3d mesh_form(shader* pshader, texture* ptexture);
  mesh_3d mesh_form(bool face_top, bool face_bottom, bool face_front, bool face_back, bool face_left, bool face_right);

  voxtype type_get();
  
  float size_get();

  static int DEFAULT_TEXTURE_RESOLUTION;
  static int DEFAULT_TEXTURE_CHANNELS;
  
 private:
  float v_size;
  
  voxcoord v_position;
  voxtype v_type;
};

class chunk{
 public:
  chunk();
  chunk(voxcoord pposition, texture* ptexpack[4], shader* pshader);

  void shader_set(shader* pshader);
  void position_set(voxcoord pposition);
  void voxel_type_set(int x, int y, int z, voxtype ptype);

  voxel* voxel_get(int x, int y, int z);

  mesh_3d mesh_form();

  shader* shader_get();
  texture* texture_pack[4];

  static int DEFAULT_CHUNK_SIZE;
  
 private:
  voxcoord c_position;
  voxel c_data[16][16][16];

  shader* c_shader;
};

#endif
