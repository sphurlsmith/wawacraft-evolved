#include "libs.h"
#include "textures.h"

// function to set generic texture attributes. this is used by wc_Texture
void nstex::setTextureAttributes(){
  // function to set the texture attributes before doing things
  // defaulted to repeat in both axes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // setting interlacing to linear for our textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
}

// loading raw image data given resolution, number of color channels to
// interpret by, the path(as std::string not c-string clutz) and the buffer
// to load the image to.
void nstex::loadRawImage(int& x, int& y, int ch, std::string n, unsigned char*& buf){
  // just a wrapper for STB-image
  buf=stbi_load(n.c_str(), &x, &y, &ch, 0);

  try{
    if(!buf){
      throw "failed-image-loading";
    }
  }catch(const char* e){
    std::cout << "Exception approached:" << e << " when trying to load file: " << n << std::endl;
  }
}

// wrapper to simply unbind textures to the default
void nstex::deactivateTextures(){
  glBindTexture(GL_TEXTURE_2D, 0);
}

// freeing texture data off memory
void nstex::freeTextureMemory(unsigned char*& v){
  stbi_image_free(v);
}

// constructor of wc_Texture, which initializes an instance
// given resolution and path as a std::string.
wc_Texture::wc_Texture(int px, int py, std::string path):
  x(px), // initializing x and y to px and py
  y(py),
  n(path){
  // keeping the image
  nstex::loadRawImage(x, y, 4, path, img); // loading into our img buffer
  
  // creating a slot in the state machine for the texture
  glGenTextures(1, &(this->TID));
  useTexture(); // binding to our texture
  nstex::setTextureAttributes(); // setting default attributes
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x,  y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img); // giving openGL the image data
  glGenerateMipmap(GL_TEXTURE_2D); // generating needed mipmaps
  nstex::deactivateTextures(); // unbinding
}

wc_Texture::~wc_Texture(){
  // nstex::freeTextureMemory(img);
}

// instance-specific function to bind the currently used texture to the
// instance
void wc_Texture::useTexture(){
  glBindTexture(GL_TEXTURE_2D, &(this->TID));
}

// getter function for the openGL object, by reference
unsigned int& wc_Texture::getTex(){
  return TID;
}
