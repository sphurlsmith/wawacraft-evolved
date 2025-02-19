#include "libs.h"
#include "shader.h"

shader::shader(const char* pvertex, const char* pfragment)
{
  std::string sourcevertex=shader::read_file(pvertex);
  std::string sourcefragment=shader::read_file(pfragment);

  unsigned int shadervertex=glCreateShader(GL_VERTEX_SHADER);
  unsigned int shaderfragment=glCreateShader(GL_FRAGMENT_SHADER);

  shader::shader_create_vertex(shadervertex, sourcevertex.c_str());
  shader::shader_create_fragment(shaderfragment, sourcefragment.c_str());

  shaderid=glCreateProgram();

  glAttachShader(shaderid, shadervertex);
  glAttachShader(shaderid, shaderfragment);
  glLinkProgram(shaderid);

  char log[512];
  int success;

  try{
    glGetProgramiv(shaderid, GL_LINK_STATUS, &success);

    if(!success){
      throw "err:w-shader-shader_linking_failed";
    }
  }catch(const char* err){
    std::cerr << err << std::endl;
    std::cerr << "OpenGL shader linking log: " << log << std::endl;
  }

  glDeleteShader(shadervertex);
  glDeleteShader(shaderfragment);
}

static void shader::shader_create_vertex(unsigned int &pshid, const char* ps)
{
  glShaderSource(pshid, 1, &ps, NULL);

  char log[512];
  int success;

  try{
    glCompileShader(pshid);
    glGetShaderiv(pshid, GL_COMPILE_STATUS, &success);

    if(!success){
      throw "err:w-shader-vertex_shader_compilation_failed";
    }
  }catch(const char* err){
    glGetShaderInfoLog(pshid, 512, NULL, log);

    std::cerr << err << std::endl;
    std::cerr << "OpenGL vertex shader compilation log: " << log << std::endl;
  }
}

static void shader::shader_create_fragment(unsigned int &pshid, const char* ps)
{
  glShaderSource(pshid, 1, &ps, NULL);

  char log[512];
  int success;

  try{
    glCompileShader(pshid);
    glGetShaderiv(pshid, GL_COMPILE_STATUS, &success);

    if(!success){
      throw "err:w-shader-fragment_shader_compilation_failed";
    }
  }catch(const char* err){
    glGetShaderInfoLog(pshid, 512, NULL, log);

    std::cerr << err << std::endl;
    std::cerr << "OpenGL fragment shader compilation log: " << log << std::endl;
  }
}

static std::string shader::read_file(const char* path)
{
  std::ifstream data_received;
  std::stringstream data_intermediate;

  std::string retstr;

  data_received.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try{
    data_received.open(path);
    
    if(data_received.good() && data_received.is_open()){
      data_intermediate << data_received.rdbuf();
    }else{
      throw "err:w-shader-file-invalid";
    }
    
    data_received.close();
  
    retstr=data_intermediate.str();
  }catch(std::ifstream::failure err){
    std::cout << "ERR: FILE " << path << " COULD NOT BE READ PROPERLY." << std::endl;
  }catch(const char* err){
    std::cout << "ERR: " << err << std::endl;
  }

  return retstr;
}

void shader::uniform_set_bool(const char* name, bool val) const
{
  glUniform1i(glGetUniformLocation(shaderid, name), val);
}

void shader::uniform_set_int(const char* name, int val) const
{
  glUniform1i(glGetUniformLocation(shaderid, name), val);
}

void shader::uniform_set_float(const char* name, float val) const
{
  glUniform1f(glGetUniformLocation(shaderid, name), val);
}

void shader::uniform_set_matrix(const char* name, float* matrix, bool transposed) const
{
  glUniformMatrix4fv(glGetUniformLocation(shaderid, name), 1, transposed, matrix);
}

void shader::activate()
{
  glUseProgram(shaderid);
}

unsigned int& shader::get_id()
{
  return shaderid;
}
