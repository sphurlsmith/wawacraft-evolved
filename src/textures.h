#ifndef TEXTURES_H
#define TEXTURES_H

#include "libs.h"

class texture
{
 public:
  texture(std::string path, int &width, int &height, int &channels, bool nearest_or_linear);

  void buffers_generate();
  void buffers_bind(int width, int height, int channels);
  
  void texture_attributes_set(bool nearest_or_linear);
  
  void image_load(std::string path, int &width, int &height, int& channels);
  void image_free();

  void texture_object_use();
  
  unsigned int* texture_object_get();
  
 private:
  unsigned int t_object;
  unsigned char* t_raw;
};

#endif
