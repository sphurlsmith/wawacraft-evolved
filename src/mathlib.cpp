#include "libs.h"
#include "mathlib.h"

quat::quat(float pw, float pi, float pj, float pk):
  w(pw),
  i(pi),
  j(pj),
  k(pk){
  
}

static float quat::norm(quat a)
{
  return sqrt(a.w*a.w+a.i*a.i+a.j*a.j+a.k*a.k);
}

static float quat::norm_nosqrt(quat a)
{
  return (a.w*a.w+a.i*a.i+a.j*a.j+a.k*a.k);
}

static quat quat::conjugate(quat a)
{
  quat ret(a.w, -a.i, -a.j, -a.k);

  return ret;
}

static quat quat::normalize(quat a)
{
  float norm=1/quat::norm(a);
 
  return quat::scalar(a, norm);
}

static quat quat::inverse(quat a)
{
  float norm_nosqrt=1/quat::norm_nosqrt(a);
  
  return quat::scalar(a, norm_nosqrt);
}

static quat quat::negate(quat a)
{
  quat ret(-a.w, -a.i, -a.j, -a.k);

  return ret;
}

static quat quat::scalar(quat a, float l)
{
  quat ret(l*a.w, l*a.i, l*a.j, l*a.k);

  return ret;
}

static quat quat::add(quat a, quat b)
{
  quat ret(a.w+b.w, a.i+b.i, a.j+b.j, a.k+b.k);

  return ret;
}

static quat quat::subtract(quat a, quat b)
{
  return quat::add(a, quat::negate(b));
}

static quat quat::product(quat a, quat b)
{
  float cw=(a.w*b.w)-(a.i*b.i+a.j*b.j+a.k*b.k);
  float ci=(a.w*b.i+b.w*a.i)+(a.j*b.k-b.j*a.k);
  float cj=(a.w*b.j+b.w*a.j)+(b.i*a.k-a.i*b.k);
  float ck=(a.w*b.k+b.w*a.k)+(a.i*b.j-b.i*a.j);
  
  quat ret(cw, ci, cj, ck);
}

static quat quat::conjugation(quat a, quat b)
{
  return quat::product(b, quat::product(a, quat::conjugate(b)));
}

vector_3d::vector_3d(float px, float py, float pz):
  x(px),
  y(py),
  z(pz){
  
}

static float vector_3d::norm(vector_3d a)
{
  return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}

static vector_3d vector_3d::negate(vector_3d a)
{
  vector_3d ret(-a.x, -a.y, a.z);

  return ret;
}

static vector_3d vector_3d::normalize(vector_3d a)
{
  float norm=1/vector_3d::norm(a);

  return vector_3d::scalar(a, norm);
}

static vector_3d vector_3d::scalar(vector_3d a, float l)
{
  vector_3d ret(l*a.x, l*a.y, l*a.z);

  return ret;
}

static vector_3d vector_3d::add(vector_3d a, vector_3d b)
{
  vector_3d ret(a.x+b.x, a.y+b.y, a.z+b.z);

  return ret;
}

static vector_3d vector_3d::subtract(vector_3d a, vector_3d b)
{
  return vector_3d::add(a, vector_3d::negate(b));
}

static vector_3d vector_3d::dot(vector_3d a, vector_3d b)
{
  vector_3d ret(a.x*b.x, a.y*b.y, a.z*b.z);

  return ret;
}

static vector_3d vector_3d::cross(vector_3d a, vector_3d b)
{
  float x=a.y*b.z-a.z*b.y;
  float y=a.x*b.z-a.z*b.x;
  float z=a.x*b.y-a.y*b.x;

  vector_3d ret(x, y, z);

  return ret;
}

matrix::matrix(float pm[4][4])
{
  for(int y=0; y<4; y++){
    for(int x=0; x<4; x++){
      m[x][y]=pm[x][y];
    }
  }
}

static matrix matrix::base()
{
  float r[4][4]=
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    };

  matrix ret(r);

  return ret;
}

// WIP WIP WIP WIP DO NOT TOUCH JUST YET

static matrix matrix::projection(float near, float far, float fov, float aspect)
{
  float n=near;
  float f=far;

  float 2n=n*2;

  float r=fov*
  
  float r[4][4]=
    {
      {2*n},
      {},
      {},
      {}
    };
}
