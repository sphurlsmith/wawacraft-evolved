#ifndef SHADER_H
#define SHADER_H

#include "libs.h"

class shader
{
 public:
  shader(const char* pvertex, const char* pfragment);
  
  static void file_read(const char* path, char* buffer)
  static void vertex_shader_create(unsigned int& pshid, const char* ps);
  static void fragment_shader_create(unsigned int& pshid, const char* ps);

  void activate();

  void uniform_bool_set(const char* name, bool val) const;
  void uniform_int_set(const char* name, int val) const;
  void uniform_float_set(const char* name, float val) const;
  void uniform_matrix_set(const char* name, float* matrix, bool transposed);

  unsigned int& id_get();
  
 private:
  unsigned int shaderid;
};

#endif
