#ifndef TEXTURES_H
#define TEXTURES_H

#include "libs.h"

// this is the textures.h header. it is used to supply utlities for loading
// and using textures on meshes during runtime. this is supplied with the
// nstex namespace, and the wc_Texture class.

// namespace of functions used to load in textures from files, and manage
// texture data in memory if needed
namespace nstex{
  // sets the default texture attributes. If i want more options, ill choose
  // them later.
  void setTextureAttributes();

  // binds GL_TEXTURE_2D to 0
  void deactivateTextures();
  // wrapper for stbi_image_free(). 
  void freeTextureMemory(unsigned char*& v);

  // loading raw image data into a buffer supplied by the caller.
  void loadRawImage(int& x, int& y, int ch, std::string n, unsigned char*& buf);
};

// a class used to intelligently create, manage, and get rid of textures in
// runtime
class wc_Texture{
 public:
  // the constructor requires the resolution and path of an image to load
  // in for our wc_Texture instance.
  wc_Texture(int px, int py, std::string path);
  ~wc_Texture();

  // instance-specific function to bind GL_TEXTURE_2D to our texture
  void useTexture();
  // function to get the reference to our raw texture openGL object
  // very rarely needed
  unsigned int& getTex();
  
 private:
  unsigned int TID;   // opengl object
  unsigned char* img; // raw image data
  
  int x; // image resolution
  int y; // y resolution

  std::string n; // path of the file
};

#endif 
