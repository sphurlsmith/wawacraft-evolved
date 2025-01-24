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
  voxel(float psize, voxcoord pposition, voxtype ptype, shader* pshader, texture* ptexture);

  void position_set(voxcoord pposition);
  void type_set(voxtype ptype);

  void mesh_form(shader* pshader, texture* ptexture);
  
  float size_get();

  mesh_3d* mesh_get();

  static int DEFAULT_TEXTURE_RESOLUTION;
  static int DEFAULT_TEXTURE_CHANNELS;
  
 private:
  float v_size;
  
  voxcoord v_position;
  voxtype v_type;
  
  mesh_3d v_mesh;
};

#endif
