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

  mesh_3d mesh_form(shader* pshader, texture* ptexture);

  std::vector<float> vertices_form(bool face_top, bool face_bottom, bool face_front, bool face_back, bool face_left, bool face_right, spritecoord psc);
  std::vector<unsigned int> indices_form(bool face_top, bool face_bottom, bool face_front, bool face_back, bool face_left, bool face_right);

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

  void shader_set(shader* pshader);
  void position_set(voxcoord pposition);
  void voxel_type_set(int x, int y, int z, voxtype ptype);

  void mesh_form();

  voxel* voxel_get(int x, int y, int z);

  mesh_3d* mesh_get();

  shader* shader_get();
  texture* spritesheet;

  static int DEFAULT_CHUNK_SIZE;
  static int DEFAULT_TEXTUREPACK_RESOLUTION;
  static int DEFAULT_TEXTUREPACK_CAPACITY;

  static float DEFAULT_BLOCK_SCALE;

 private:
  voxcoord c_position;
  voxel c_data[16][16][16];

  mesh_3d c_mesh;
  shader* c_shader;
};

#endif
