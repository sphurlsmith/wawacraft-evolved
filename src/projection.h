#ifndef PROJECTION_H
#define PROJECTION_H

#include "libs.h"

// this is the projection.h header. It is used as a utility for performing mathematical operations
// of many different types, with its main intent being to supply utilities to create projection
// transformations, hence the name.

class quat{
public:
  quat(float pw, float pi, float pj, float pk);

  quat conjugate();
  quat normal();
  quat inverse();
  
  static quat add(const quat& a, const quat& b);
  static quat subtract(const quat& a, const quat& b);
  
  static quat product(const quat& a, const quat& b);

  static float dotProduct(const quat& a, const quat& b);
  
  float conjugateProduct();

  float norm();
  
  float w;
  float i;
  float j;
  float k;
};

// this is the namespace which contains a majority of the utilities for projection mathematics
// as well as the structs and typedefs used to define mathematical structures like vectors and arrays
namespace nsproj{
  // for angle unit conversions
  const float PI=3.141592653589;
  const float DEG=180;

  const float DEGTORAD=PI/180;
  const float RADTODEG=1/DEGTORAD;
  
  // 3-dimensional vector
  struct vec3{
    float x=1;
    float y=1;
    float z=1;
  };

  // 3-dimensional vector in homogenous coordinates
  struct vec4{
    float x=1;
    float y=1;
    float z=1;
    float w=1;
  };

  // 4x4 matrix
  typedef struct{
    float m[4][4]={
      {1,0,0,0},
      {0,1,0,0},
      {0,0,1,0},
      {0,0,0,1}
    };
  } mat4;

  // vec3 utility functions
  vec3 translateVec3(vec3 a, vec3 b);    // translating a vector by another
  vec3 subtractVec3(vec3 a, vec3 b);     // subtracting vectors b from a
  vec3 scaleVec3(vec3 a, float scalar);  // scaling a vector by a scalar

  vec3 dot(vec3 a, vec3 b);              // dot product
  vec3 cross(vec3 a, vec3 b);            // cross product
  
  vec3 rotateVec3Quat(vec3 v, vec3 axis, float a);
  
  vec3 rotateVec3XY(vec3 v, float a);      // rotating a vector by a radian angle
  vec3 rotateVec3YZ(vec3 v, float a);      // in the yz plane
  vec3 rotateVec3XZ(vec3 v, float a);      // in the xz plane

  float getMagnitude(vec3 v);            // finding the magnitude of a regular vector
  vec3 normalizeVec3(vec3 v);            // using the magnitude to find the normalized version of a vec3
  
  vec3 normalizeVec4(vec4 v);            // normalizing a vec4 to a vec3
  vec3 vec4To3(vec4 v);                  // getting a vec3 from a vec4 without normalizing
  
  // vec4 utility functions
  vec4 homogenizeVector(vec3 v);         // get a homogenous vector from a 3d vector
  
  // matrix utility functions
  mat4 multiplyMatrices(mat4 a, mat4 b); // multiplies two matrices
  mat4 transposeMatrix(mat4 m);          // transpose a matrix from row major to column major

  mat4 baseMatrix();
  mat4 identityMatrix();                                                            // classic identity matrix
  mat4 rotateMatrixXY(float a);                                                     // creating an XY rotation matrix
  mat4 rotateMatrixYZ(float a);                                                     // creating a YZ rotation matrix
  mat4 rotateMatrixXZ(float a);                                                     // creating an XZ rotation matrix
  mat4 scaleMatrix(vec3 v);                                                         // scaling matrix
  mat4 translationMatrix(vec3 v);                                                   // translation matrix
  mat4 perspectiveProjectionMatrix(float fov, float aspect, float near, float far); // perspective projection matrix
  mat4 modelMatrix(vec3 rot, vec3 tran, float s);                               // scale, rotation, and translation all in 1
  mat4 viewMatrix(vec3 up, vec3 target, vec3 tran);
  
  // misc
  vec4 vec4Xmat4(vec4 a, mat4 m);               // multiplying a vec4 by a matrix
  vec4 operator*(const vec4& a, const mat4& m); // operator overloading for vec4Xmat4
  vec4& operator*=(vec4& a, const mat4& m);     // operator overloading in case somebody wants to use vec4*=mat4

  mat4 operator*(const mat4& a, const mat4& m);
  mat4& operator*=(mat4& a, const mat4& m);

  // debug
  void debugOutputMatrix(mat4 m);
};

#endif
