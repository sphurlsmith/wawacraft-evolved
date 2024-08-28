#ifndef TEXTURES_H
#define TEXTURES_H

#include "libs.h"

namespace nstex{
  void setTextureAttributes();
  
  void useTexture(unsigned int t);
  void deactivateTextures();
  void freeTextureMemory(unsigned char* v);
  
  unsigned char* loadRawImage(int& x, int& y, int ch, std::string n);
};

class wc_Texture{
 public:
  wc_Texture(int px, int py, std::string path);
  ~wc_Texture();
  
  unsigned int getTex();
  
 private:
  unsigned int TID;

  int x;
  int y;

  std::string n;
};

#endif 
