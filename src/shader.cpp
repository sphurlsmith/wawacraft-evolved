#include "libs.h"
#include "shader.h"

// this is the implementation of the methods within the shader.h header.

// utility function used to read in text files given the relative path, passed
// as a c-string by reference, which also returns a string.
// TODO: create an overload that uses a std::string for the path
std::string nsshader::readFile(const char*& path){
  std::ifstream fsl;     // the stream by which we receive file data
  std::stringstream fss; // the intermediate buffer where the file data resides

  std::string s; // the final buffer returned to the caller

  // preventing any corrupted/faulty files
  fsl.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try{
    fsl.open(path); // opening the file path
    if(fsl.good() && fsl.is_open()){
      fss << fsl.rdbuf(); // reading in the read buffer of the file
    }else{
      throw "faulty-file or file-not-open"; // faulty file/doesnt exist
    }
    
    fsl.close(); // closing it to prevent any useless memory bottlenecking
  
    s=fss.str(); // reading in from the stringstream buffer
  }catch(std::ifstream::failure err){
    std::cout << "ERROR APPROACHED: FILE " << path << " COULD NOT BE READ PROPERLY." << std::endl;
  }catch(const char* err){
    std::cout << "ERROR APPROACHED: " << err << std::endl;
  }

  return s;
}

// cosntructor of the shader class. Constructs a shader given the path of its
// source files
shader::shader(const char* vertexp, const char* fragmentp){
  std::string vertexs=nsshader::readFile(vertexp);     // reads in the file text
  std::string fragments=nsshader::readFile(fragmentp); // for vertex & fragment

  // compiling the vertex and fragment files in temporary objects
  unsigned int vertexshader=glCreateShader(GL_VERTEX_SHADER);
  createVertexShader(vertexshader, vertexs.c_str());

  // here done for the fragment shader too
  unsigned int fragmentshader=glCreateShader(GL_FRAGMENT_SHADER);
  createFragmentShader(fragmentshader, fragments.c_str());

  ID=glCreateProgram(); // initializing the complete program

  // attaching the vertex and fragment objects to the program
  glAttachShader(ID, vertexshader);
  glAttachShader(ID, fragmentshader);

  glLinkProgram(ID); // links the compiled, usable shader program

  // from here on, we try to see if anything happened during the linking
  // process. Most of the time it follows the same formula:
  /*
    1. create a log string and a success flag
    2. ask OpenGL if anything happened during what we did for the
       shader.
    3. If we did, throw an exception, and send an error message
    4. otherwise, continue on happily ever after
   */
  char log[512]; // step 1
  int success;
  
  try{
    // the methods vary, since overloading isnt a thing in C, but
    // it is essentially is the same thing
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if(!success){throw "failed-shader-linking";}
  }catch(const char* err){
    glGetProgramInfoLog(ID, 512, NULL, log); // grabbing OpenGL's error log

    std::cout << "Exception approached: " << err << std::endl; // error message
    std::cout << "OpenGL shader linking log:\n" << log << std::endl; // log
  }

  // we just clear the memory of the single object files of the
  // shader sources, since we already have a linked program
  glDeleteShader(vertexshader);
  glDeleteShader(fragmentshader);
}

// function that compiles a vertex shader object given its source code
// passed as a c string
static void shader::createVertexShader(unsigned int& shaderet, const char* s){
  glShaderSource(shaderet, 1, &s, NULL); // loading in the source

  // this is about the exact same process we had before with the shader program
  // but for individual shaders
  char log[512];
  int success;
  
  try{
    glCompileShader(shaderet); // compiling the shader
    glGetShaderiv(shaderet, GL_COMPILE_STATUS, &success); // seeing if we succeeded

    if(!success){
      // this here is why we have two different functions for what
      // is basically the same process. There needs to be a differentiation
      // for our vertex errors and fragment errors.
      throw "failed-vertex-shader-compilation";
    }
  }catch(const char* err){
    glGetShaderInfoLog(shaderet, 512, NULL, log); // getting OpenGL's log
    
    std::cout << "Exception approached: " << err << std::endl; // error message
    std::cout << "OpenGL shader compilation log:\n" << log << std::endl; // log
  }
}

// function that compiles a given fragment shader object, given its source code
// as a c-string. Read the documentation of the vertex shader program, in order
// to understand how this function operates. Both functions are essentially
// doing the same thing but iwth variation
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

// binding render calls and other things that require a shader towards our
// own shader. Instance specific
void shader::activate(){
  glUseProgram(ID);
}

// from here on, the rest are setter functions that serve as wrappers
// for the uglier glUniform calls. They need no documentation.

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

// returns the reference to the shader ID. rarely needed but its here
// just in case
unsigned int& shader::getID(){
  return ID;
}
