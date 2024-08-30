#ifndef SHADER_H
#define SHADER_H

#include "libs.h"

// shader.h is a header that provides the nsshader utility namespace and the class shader, which
// provides support to create and manage shaders intelligently

// utility namespace used to read in shader source files (.glsl)
// mostly used by shader class, but we could find that some other need for this
namespace nsshader{
  // returns the string of a complete file given its relative path from the
  // program's working directory, given as a c-string passed by reference
  std::string readFile(const char*& path);
}

// class used to create, manage, and get rid of shaders intelligently. this class
// allows you to also set uniforms of different variables in the shader source.
class shader{
 public:
  // the constructor simply builds a shader object given the path of the vertex
  // and fragment shader
  shader(const char* vertexp, const char* fragmentp);

  // static functions to compile vertex and fragment shaders given the complete
  // source code of the said shaders, and the opengl object of which the compiled
  // source will be attached to, passed by reference
  static void createVertexShader(unsigned int& shaderet, const char* s);
  static void createFragmentShader(unsigned int& shaderet, const char* s);

  // an instance specific function used to bind any further rendering to be
  // binded to the shader
  void activate();

  // setting specific uniform values within a shader given the name and desired
  // value
  void setUniformBool(const char* n, bool val) const;
  void setUniformInt(const char* n, int val) const;
  void setUniformFloat(const char* n, float val) const;
  void setUniformMatrix(const char* n, bool transpose, float *m) const;

  // function that returns the ID of a shader(by reference, im not scamming ya!)
  unsigned int& getID();

 private:

  // the OpenGL ID for the shader program, initialized in the constructor.
  unsigned int ID;
};

#endif
