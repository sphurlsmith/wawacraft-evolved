#ifndef MATHLIB_H
#define MATHLIB_H

#include "libs.h"

class quat
{
 public:
  quat(float pw, float pi, float pj, float pk);

  static float norm(quat a);
  static float norm_nosqrt(quat a);
  
  static quat conjugate(quat a);
  static quat normalize(quat a);
  static quat inverse(quat a);
  static quat negate(quat a);

  static quat scalar(quat a, float l);
  
  static quat add(quat a, quat b);
  static quat subtract(quat a, quat b);
  static quat product(quat a, quat b);

  static quat conjugation(quat a, quat b);
  
  float w;
  float i;
  float j;
  float k;
};

class vector_3d
{
 public:
  vector_3d(float px, float py, float pz);

  static float norm(vector_3d a);
  
  static vector_3d negate(vector_3d a);
  static vector_3d normalize(vector_3d a);
  static vector_3d scalar(vector_3d a, float l);

  static vector_3d add(vector_3d a, vector_3d b);
  static vector_3d subtract(vector_3d a, vector_3d b);
  static vector_3d dot(vector_3d a, vector_3d b);
  static vector_3d cross(vector_3d a, vector_3d b);
  
  float x;
  float y;
  float z;
};

class matrix
{
 public:
  matrix(float pm[4][4]);
  
  static matrix base();

  static matrix projection(float near, float far, float fov, float aspect);
  static matrix model(float axy, float ayz, float axz, float sx, float sy, float sz);
  static matrix view(vector_3d target, vector_3d up, vector_3d translation);

  static matrix quaternion(quat a);

  static matrix multiply(matrix a, matrix b);
  static matrix transpose(matrix a);

  float m[4][4];
};

class vector_homogenous:vector_3d
{
 public:
  vector_homogenous(float x, float y, float z, float w);

  static vector_homogenous homogenize(vector_homogenous a);
  static vector_homogenous multiplyMatrix(vector_homogenous v, matrix m);
  
  float w;
};

#endif
