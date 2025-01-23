#include "libs.h"
#include "textures.h"

texture::texture(std::string path, int &width, int &height, int &channels, bool nearest_or_linear)
{
  buffers_generate();

  texture_object_use();
  texture_attributes_set(nearest_or_linear);
  
  image_load(path, width, height, channels);
  buffers_bind(width, height);
  image_free();
}

void texture::buffers_generate()
{
  glGenTextures(1, &t_object);
}

void texture::buffers_bind(int width, int height)
{
  if(t_raw){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, t_raw);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cerr << "err:texture-buffers_bind-t_raw-invalid" << std::endl;
  }
}

void texture::texture_attributes_set(bool nearest_or_linear)
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  if(nearest_or_linear){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  }else{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  }
}

void texture::image_load(std::string path, int &width, int &height, int& channels)
{
  stbi_set_flip_vertically_on_load(true);
  t_raw=stbi_load(path.c_str(), &width, &height, &channels, 0);
}

void texture::image_free()
{
  stbi_image_free(t_raw);
}

void texture::texture_object_use()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, t_object);
}

unsigned int* texture::texture_object_get()
{
  return &t_object;
}
