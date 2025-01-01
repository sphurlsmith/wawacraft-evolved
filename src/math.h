#ifndef MATH_H
#define MATH_H

#include "libs.h"

class vector_3d
{
 public:
  vector_3d(float x, float y, float z);

  static vector_3d translate(vector_3d a, vector_3d b);

  static vector_3d dot_product(vector_3d a, vector_3d b);
  static vector_3d cross_product(vector_3d a, vector_3d b);
  
  vector_3d negate();
    
  float x;
  float y;
  float z;
};

#endif
