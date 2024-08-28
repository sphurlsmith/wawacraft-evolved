#include "libs.h"
#include "textures.h"

void nstex::setTextureAttributes(){
  // function to set the texture attributes before doing things
  // defaulted to repeat in both axes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // setting interlacing to linear for our textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
}

unsigned char* nstex::loadRawImage(int& x, int& y, int ch, std::string n){
  // just a wrapper for STB-image
  static unsigned char* ret=stbi_load(n.c_str(), &x, &y, &ch, 0);

  try{
    if(ret){
      return ret; // will this be valid data i wonder?
    }else{
      throw "failed-image-loading";
    }
  }catch(const char* e){
    std::cout << "Exception approached:" << e << " when trying to load file: " << n << std::endl;
  }
}

void nstex::deactivateTextures(){
  glBindTexture(GL_TEXTURE_2D, 0);
}

void nstex::freeTextureMemory(unsigned char* v){
  stbi_image_free(v);
}

wc_Texture::wc_Texture(int px, int py, std::string path):
  x(px),
  y(py),
  n(path){
  // keeping the image
  unsigned char* img=nstex::loadRawImage(x, y, 4, path);
  
  // creating a slot in the state machine for the texture
  glGenTextures(1, &(this->TID));
  useTexture(); // binding to our texture
  nstex::setTextureAttributes(); // setting default attributes
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x,  y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img); // giving openGL the image data
  glGenerateMipmap(GL_TEXTURE_2D); // generating needed mipmaps
  nstex::deactivateTextures(); // unbinding
}

wc_Texture::~wc_Texture(){
  
}

void wc_Texture::useTexture(){
  glBindTexture(GL_TEXTURE_2D, &(this->TID));
}

unsigned int wc_Texture::getTex(){
  return TID;
}
