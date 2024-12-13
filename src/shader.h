#ifndef SHADER_H
#define SHADER_H

#include "libs.h"

class shader
{
 public:
  shader(const char* pvertex, const char* pfragment);
  
  static void shader_create_vertex(unsigned int& pshid, const char* ps);
  static void shader_create_fragment(unsigned int& pshid, const char* ps);

  static std::string read_file(const char* path);

  void uniform_set_bool(const char* name, bool val) const;
  void uniform_set_int(const char* name, int val) const;
  void uniform_set_float(const char* name, float val) const;
  void uniform_set_matrix(const char* name, float* matrix, bool transposed) const;

  void activate();
  
  unsigned int& get_id();
  
 private:
  unsigned int shaderid;
};

#endif
