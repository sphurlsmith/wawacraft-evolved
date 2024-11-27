#include "libs.h"
#include "shader.h"

shader::shader(const char* pvertex, const char* pfragment)
{
  char* vertex_source;
  shader::file_read(pvertex, &vertex_source);
}
