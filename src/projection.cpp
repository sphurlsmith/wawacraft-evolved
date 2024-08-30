#include "libs.h"
#include "projection.h"

// this is the implementation for the projection.h header

nsproj::vec3 nsproj::translateVec3(nsproj::vec3 a, nsproj::vec3 b){
  return {
    a.x+b.x,
    a.y+b.y,
    a.z+b.z
  };
}

nsproj::vec3 nsproj::subtractVec3(nsproj::vec3 a, nsproj::vec3 b){
  return nsproj::translateVec3(a, {-b.x, -b.y, -b.z});
}

nsproj::vec3 nsproj::scaleVec3(nsproj::vec3 a, float scalar){
  return {
    a.x*scalar,
    a.y*scalar,
    a.z*scalar
  };
}

nsproj::vec3 nsproj::rotateVec3XY(nsproj::vec3 v, float a){
  return {
    ((v.x*cos(a))-(v.y*sin(a))),
    ((v.y*cos(a))+(v.x*sin(a))),
    v.z
  };
}

nsproj::vec3 nsproj::rotateVec3YZ(nsproj::vec3 v, float a){
  return {
    v.x,
    ((v.y*cos(a))+(v.z*sin(a))),
    ((v.z*cos(a))-(v.y*sin(a)))
  };
}

nsproj::vec3 nsproj::rotateVec3XZ(nsproj::vec3 v, float a){
  return {
    ((v.x*cos(a))+(v.z*sin(a))),
    v.y,
    ((v.z*cos(a))-(v.x*sin(a)))
  };
}

nsproj::vec3 nsproj::normalizeVec4(nsproj::vec4 v){
  return {
    (v.x/v.w),
    (v.y/v.w),
    (v.z/v.w)
  };
}

nsproj::vec3 nsproj::vec4To3(nsproj::vec4 v){
  return {
    v.x,
    v.y,
    v.z
  };
}

nsproj::vec4 nsproj::homogenizeVector(nsproj::vec3 v){
  return {
    v.x,
    v.y,
    v.z,
    1
  };
}

nsproj::mat4 nsproj::multiplyMatrices(nsproj::mat4 a, nsproj::mat4 b){
  nsproj::mat4 ret;

  for(int y=0; y<4; y++){
    for(int x=0; x<4; x++){
      ret[x][y]=(a[0][y]*b[y][x])+(a[1][y]*b[y][x])+(a[2][y]*b[y][x])+(a[3][y]*b[y][x]);
    }
  }

  return ret;
}

nsproj::mat4 nsproj::transposeMatrix(nsproj::mat4 m){
  nsproj::mat4 r;

  for(int x=0; x<4; x++){
    for(int y=0; y<4; y++){
      r[x][y]=m[y][x];
    }
  }

  return r;
}

nsproj::mat4 nsproj::identityMatrix(){
  return {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };
}

nsproj::mat4 nsproj::rotateMatrixXY(float a){
  return {
    {cos(a), -sin(a), 0, 0},
    {sin(a),  cos(a), 0, 0},
    {0,       0,      1, 0},
    {0,       0,      0, 1}
  };
}

nsproj::mat4 nsproj::rotateMatrixYZ(float a){
  return {
    {1, 0,       0,      0},
    {0, cos(a), -sin(a), 0},
    {0, sin(a),  cos(a), 0},
    {0, 0,       0,      1}
  };
}

nsproj::mat4 nsproj::rotateMatrixXZ(float a){
  return {
    {cos(a), 0, -sin(a),  0},
    {0,      0,  0,       0},
    {sin(a), 0,  cos(a),  0},
    {0,      0,  0,       1}
  };
}


nsproj::mat4 nsproj::scaleMatrix(vec3 v){
  return {
    {v.x, 0,   0,   0},
    {0,   v.y, 0,   0},
    {0,   0,   v.z, 0},
    {0,   0,   0,   1}
  };
}

nsproj::mat4 nsproj::translationMatrix(vec3 v){
  return {
    {1, 0, 0, v.x},
    {0, 1, 0, v.y},
    {0, 0, 1, v.z},
    {0, 0, 0,   1}
  };
}

nsproj::vec4 nsproj::vec4Xmat4(nsproj::vec4 a, nsproj::mat4 m){
  nsproj::vec4 ret;

  for(int x=0; x<4; x++){
    ret[x]=(m[0][x]*a[0])+(m[1][x]*a[1])(m[2][x]*a[2])(m[3][x]*a[3]);
  }

  return ret;
}

nsproj::vec4 operator*(const nsproj::vec4& a, const nsproj::mat4& m){
  return nsproj::vec4Xmat4(a, m);
}

nsproj::vec4& operator*=(nsproj::vec4& a, const nsproj::mat4& m){
  a=nsproj::vec4Xmat4(a, m);
}
