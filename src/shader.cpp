#include "libs.h"
#include "shader.h"

std::string nsshader::readFile(const char*& path){
  std::ifstream fsl;
  std::stringstream fss;

  std::string s;
  
  fsl.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try{
    fsl.open(path);
    if(fsl.good() && fsl.is_open()){
      fss << fsl.rdbuf();
    }else{
      throw "faulty-file or file-not-open";
    }
    
    fsl.close();
  
    s=fss.str();
  }catch(std::ifstream::failure err){
    std::cout << "ERROR APPROACHED: FILE " << path << " COULD NOT BE READ PROPERLY." << std::endl;
  }catch(const char* err){
    std::cout << "ERROR APPROACHED: " << err << std::endl;
  }

  return s;
}

shader::shader(const char* vertexp, const char* fragmentp){
  std::string vertexs=nsshader::readFile(vertexp);
  std::string fragments=nsshader::readFile(fragmentp);
  
  unsigned int vertexshader=glCreateShader(GL_VERTEX_SHADER);
  createVertexShader(vertexshader, vertexs.c_str());
  
  unsigned int fragmentshader=glCreateShader(GL_FRAGMENT_SHADER);
  createFragmentShader(fragmentshader, fragments.c_str());

  ID=glCreateProgram();
  
  glAttachShader(ID, vertexshader);
  glAttachShader(ID, fragmentshader);

  glLinkProgram(ID);

  char log[512];
  int success;
  
  try{
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if(!success){throw "failed-shader-linking";}
  }catch(const char* err){
    glGetProgramInfoLog(ID, 512, NULL, log);

    std::cout << "Exception approached: " << err << std::endl;
    std::cout << "OpenGL shader linking log:\n" << log << std::endl;
  }

  glDeleteShader(vertexshader);
  glDeleteShader(fragmentshader);
}

static void shader::createVertexShader(unsigned int& shaderet, const char* s){
  glShaderSource(shaderet, 1, &s, NULL);
  
  char log[512];
  int success;
  
  try{
    glCompileShader(shaderet);
    glGetShaderiv(shaderet, GL_COMPILE_STATUS, &success);

    if(!success){
      throw "failed-vertex-shader-compilation";
    }
  }catch(const char* err){
    glGetShaderInfoLog(shaderet, 512, NULL, log);
    
    std::cout << "Exception approached: " << err << std::endl;
    std::cout << "OpenGL shader compilation log:\n" << log << std::endl;
  }
}

static void shader::createFragmentShader(unsigned int& shaderet, const char* s){
  glShaderSource(shaderet, 1, &s, NULL);

  char log[512];
  int success;

  try{
    glCompileShader(shaderet);
    glGetShaderiv(shaderet, GL_COMPILE_STATUS, &success);
    
    if(!success){
      throw "failed-fragment-shader-compilation";
    }
  }catch(const char* err){
    glGetShaderInfoLog(shaderet, 512, NULL, log);
    
    std::cout << "Exception approached: " << err << std::endl;
    std::cout << "OpenGL shader compilation log:\n" << log << std::endl;
  }
}

void shader::activate(){
  glUseProgram(ID);
}

void shader::setUniformBool(const char* n, bool val) const{
  glUniform1i(glGetUniformLocation(ID, n), val);
}

void shader::setUniformInt(const char* n, int val) const{
  glUniform1i(glGetUniformLocation(ID, n), val);
}

void shader::setUniformFloat(const char* n, float val) const{
  glUniform1f(glGetUniformLocation(ID, n), val);
}

void shader::setUniformMatrix(const char* n, bool transpose, float *m) const{
  glUniformMatrix4fv(glGetUniformLocation(ID, n), 1, transpose, m);
}

unsigned int shader::getID(){
  return ID;
}
