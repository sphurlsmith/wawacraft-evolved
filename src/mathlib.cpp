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

  return ret;
}

static quat quat::conjugation(quat a, quat b)
{
  return quat::product(b, quat::product(a, quat::inverse(b)));
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
  vector_3d ret(-a.x, -a.y, -a.z);

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

static float vector_3d::dot_sum(vector_3d a, vector_3d b)
{
  vector_3d ret=vector_3d::dot(a, b);

  return (ret.x+ret.y+ret.z);
}

static vector_3d vector_3d::cross(vector_3d a, vector_3d b)
{
  float x=a.y*b.z-a.z*b.y;
  float y=a.x*b.z-a.z*b.x;
  float z=a.x*b.y-a.y*b.x;

  vector_3d ret(x, y, z);

  return ret;
}

static float vector_3d::cross_sum(vector_3d a, vector_3d b)
{
  vector_3d ret=vector_3d::cross(a, b);

  return (ret.x+ret.y+ret.z);
}

vector_homogenous::vector_homogenous(float px, float py, float pz, float pw):
  vector_3d::vector_3d(px, py, pz),
  w(pw){
  
}

static vector_homogenous vector_homogenous::homogenize(vector_homogenous a)
{
  vector_homogenous ret(a.x/a.w, a.y/a.w, a.z/a.w, 1);

  return ret;
}

static vector_homogenous vector_homogenous::faux_dot(vector_homogenous a, vector_homogenous b)
{
  vector_homogenous ret(a.x*b.x, a.y*b.y, a.z*b.z, a.w*a.w);

  return ret;
}

static float vector_homogenous::faux_dot_sum(vector_homogenous a, vector_homogenous b)
{
  vector_homogenous ret=vector_homogenous::faux_dot(a, b);

  return (ret.x+ret.y+ret.z+ret.w);
}

static vector_homogenous vector_homogenous::faux_scalar(vector_homogenous a, float l)
{
  vector_homogenous ret(l*a.x, l*a.y, l*a.z, l*a.w);

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

static matrix matrix::translation(vector_3d a)
{
  float r[4][4]=
    {
      {1, 0, 0, a.x},
      {0, 1, 0, a.y},
      {0, 0, 1, a.z},
      {0, 0, 0,   1}
    };

  matrix ret(r);

  return ret;
}

static matrix matrix::projection(float near, float far, float fov, float aspect)
{
  float n=near;
  float f=far;

  float tanfov=tan(fov*(MATHLIB_PI/180)/2);

  float fr=n*tanfov;
  float ft=fr*aspect;
  float fl=-fr;
  float fb=-ft;
  
  float rs[4][4]=
    {
      {(2*n)/(fr-fl),    0,      (fr+fl)/(fr-fl),          0},
      {     0,    (2*n)/(ft-fb), (ft+fb)/(ft-fb),          0},
      {     0,           0,      (f+n)/(f-n), -(2*f*n)/(f-n)},
      {     0,           0,           -1,                  0}
    };

  matrix ret(rs);
  
  ret.m[0][0]=(2*n)/(fr-fl);
  ret.m[0][2]=(fr+fl)/(fr-fl);
  
  ret.m[1][1]=(2*n)/(ft-fl);
  ret.m[1][2]=(ft+fb)/(ft-fb);

  ret.m[2][2]=(f+n)/(f-n);
  ret.m[2][3]=(-2*f*n)/(f-n);

  ret.m[3][2]=1;

  return ret;
}

static matrix matrix::model(float x, float y, float z, float s, vector_3d t)
{
  quat rotorx(cos(x/2), sin(x/2), 0, 0);
  quat rotory(cos(y/2), 0, sin(y/2), 0);
  quat rotorz(cos(z/2), 0, 0, sin(z/2));

  quat rotor=quat::product(rotorz, quat::product(rotory, rotorx));
  
  float scs[4][4]=
    {
      {s, 0, 0, 0},
      {0, s, 0, 0},
      {0, 0, s, 0},
      {0, 0, 0, 1}
    };

  matrix scale(scs);
  matrix translation=matrix::translation(t);

  matrix ret(matrix::base().m);

  // brother what is this... matrix multiplication without operators... holy shit
  ret=matrix::multiply(matrix::multiply(scale, matrix::quaternion(rotor)), translation);

  return ret;
}

static matrix matrix::view(vector_3d target, vector_3d up, vector_3d translation)
{
  vector_3d left(1, 0, 0);

  target=vector_3d::normalize(target);
  
  left=vector_3d::normalize(vector_3d::cross(up, target));
  up=vector_3d::normalize(vector_3d::cross(left, target));

  matrix translation_matrix=matrix::translation(vector_3d::negate(translation));

  float v[4][4]=
    {
      {left.x, up.x, target.x, 0},
      {left.y, up.y, target.y, 0},
      {left.z, up.z, target.z, 0},
      {  0,      0,      0,    1}
    };

  matrix rotations(v);
  matrix::transpose(rotations);
  
  matrix ret=matrix::multiply(translation_matrix, rotations);

  return ret;
}

static matrix matrix::quaternion(quat a)
{
  float w=a.w;
  float i=a.i;
  float j=a.j;
  float k=a.k;
  
  float r[4][4]=
    {
      {w*w+i*i-j*j-k*k,   2*i*j-2*w*k,     2*i*k+2*w*j,   0},
      {  2*i*j+2*w*k,   w*w-i*i+j*j-k*k,   2*j*k-2*w*i,   0},
      {  2*i*j-2*w*j,     2*j*k+2*w*i,   w*w-i*i-j*j+k*k, 0},
      {       0,               0,               0,        1}
    };

  matrix ret(r);

  return r;
}

static matrix matrix::multiply(matrix a, matrix b)
{
  float r[4][4];

  for(int y=0; y<4; y++){
    for(int x=0; x<4; x++){
      r[x][y]=0;
      for(int z=0; z<4; z++){
	r[x][y]+=a.m[z][y]*b.m[x][z];
      }
    }
  }
  
  matrix ret(r);

  return ret;
}

static void matrix::transpose(matrix &a)
{
  for(int y=0; y<4; y++){
    for(int x=0; x<4; x++){
      float t=a.m[y][x];
      a.m[y][x]=a.m[x][y];
      a.m[x][y]=t;
    }
  }
}

static vector_homogenous matrix::vector_multiply(matrix m, vector_homogenous v)
{
  vector_homogenous x(m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0]);
  vector_homogenous y(m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1]);
  vector_homogenous z(m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2]);
  vector_homogenous w(m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);

  vector_homogenous ret(vector_homogenous::faux_dot_sum(x, v),
			vector_homogenous::faux_dot_sum(y, v),
			vector_homogenous::faux_dot_sum(z, v),
			vector_homogenous::faux_dot_sum(w, v));
  
  return ret;
}

void matrix::debug_output()
{
  std::cout << "MATRIX DEBUG OUTPUT" << std::endl;
  for(int y=0; y<4; y++){
    for(int x=0; x<4; x++){
      std::cout << m[y][x] << ' ';
    }
    std::cout << std::endl;
  }
}
