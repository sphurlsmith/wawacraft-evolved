#ifndef TEXTURES_H
#define TEXTURES_H

#include "libs.h"

namespace nstex{
  void setTextureAttributes();
  
  void deactivateTextures();
  void freeTextureMemory(unsigned char* v);
  
  void loadRawImage(int& x, int& y, int ch, std::string n, unsigned char*& buf);
};

class wc_Texture{
 public:
  wc_Texture(int px, int py, std::string path);
  ~wc_Texture();
  
  void useTexture();
  unsigned int getTex();
  
 private:
  unsigned int TID;
  unsigned char* img;
  
  int x;
  int y;

  std::string n;
};

#endif 
