#ifndef SHADER_H
#define SHADER_H

#include "libs.h"

namespace nsshader{
  std::string readFile(const char*& path);
}

class shader{
 public:
  shader(const char* vertexp, const char* fragmentp);

  static void createVertexShader(unsigned int shaderet, const char* s);
  static void createFragmentShader(unsigned int shaderet, const char* s);
  
  void activate();
  
  void setUniformBool(const char* n, bool val) const;
  void setUniformInt(const char* n, int val) const;
  void setUniformFloat(const char* n, float val) const;
  void setUniformMatrix(const char* n, bool transpose, float *m) const;
  
  unsigned int getID();

 private:
  
  unsigned int ID;
};

#endif
