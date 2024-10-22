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

nsproj::vec3 nsproj::dot(nsproj::vec3 a, nsproj::vec3 b){
  return {
    a.x*b.x,
    a.y*b.y,
    a.z*b.z
  };
}

nsproj::vec3 nsproj::cross(nsproj::vec3 a, nsproj::vec3 b){
  float deti=(a.y*b.z-a.z*b.y);
  float detj=(a.x*b.z-a.z*b.x);
  float detk=(a.x*b.y-a.y*b.x);

  return {
    deti,
    detj,
    detk
  };
}

nsproj::vec3 nsproj::rotateVec3Quat(nsproj::vec3 v, nsproj::vec3 axis, float a){
  float cosha=cos(a/2);
  float sinha=sin(a/2);
  
  quat rt(cosha, sinha*axis.x, sinha*axis.y, sinha*axis.z);
  rt=rt.normal();

  quat rtc=rt.conjugate();
  quat q(0, v.x, v.y, v.z);
  
  quat retq=quat::product(rt, quat::product(q, rtc));

  nsproj::vec3 ret={retq.i, retq.j, retq.k};

  return ret;
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

float nsproj::getMagnitude(vec3 v){
  return (sqrt(v.x*v.x+v.y*v.y+v.z*v.z));
}

nsproj::vec3 nsproj::normalizeVec3(vec3 v){
  float m=nsproj::getMagnitude(v);
  
  return {
    v.x/m,
    v.y/m,
    v.z/m
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
      float i=0;
      for(int z=0; z<4; z++){
	i+=(a.m[z][y]*b.m[x][z]);
      }
      ret.m[x][y]=i;
    }
  }
  
  return ret;
}

nsproj::mat4 nsproj::transposeMatrix(nsproj::mat4 m){
  nsproj::mat4 r;

  for(int x=0; x<4; x++){
    for(int y=0; y<4; y++){
      r.m[x][y]=m.m[y][x];
    }
  }

  return r;
}

nsproj::mat4 nsproj::baseMatrix(){
  return {
    {
      {1,1,1,1},
      {1,1,1,1},
      {1,1,1,1},
      {1,1,1,1}
    }
  };
}

nsproj::mat4 nsproj::identityMatrix(){
  return {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };
}

nsproj::mat4 nsproj::rotateMatrixXY(float a){
  return {
    {
      {cos(a), -sin(a),  0,      0},
      {sin(a),  cos(a),  0,      0},
      {0,       0,       1,      0},
      {0,       0,       0,      1}
    }
  };
}

nsproj::mat4 nsproj::rotateMatrixYZ(float a){
  return {
    {
      {1, 0,       0,      0},
      {0, cos(a), -sin(a), 0},
      {0, sin(a),  cos(a), 0},
      {0, 0,       0,      1}
    }
  };
}

nsproj::mat4 nsproj::rotateMatrixXZ(float a){
  return {
    {
      {cos(a), 0, -sin(a),  0},
      {0,      1,  0,       0},
      {sin(a), 0,  cos(a),  0},
      {0,      0,  0,       1}
    }
  };
}


nsproj::mat4 nsproj::scaleMatrix(vec3 v){
  return {
    {
      {v.x, 0,   0,   0},
      {0,   v.y, 0,   0},
      {0,   0,   v.z, 0},
      {0,   0,   0,   1}
    }
  };
}

nsproj::mat4 nsproj::translationMatrix(vec3 v){
  return {
    {
      {1, 0, 0, v.x},
      {0, 1, 0, v.y},
      {0, 0, 1, v.z},
      {0, 0, 0,   1}
    }
  };
}

// simply creates a perspective projection matrix
// in openGL style, hence negating Z values
nsproj::mat4 nsproj::perspectiveProjectionMatrix(float fov, float aspect, float near, float far){
  // using the FOV from given angle
  float tanfov=tan(fov/2);
  
  // defining frustum dimensions
  float frig=near*tanfov;
  float ftop=frig*aspect;
  float flef=-frig;
  float fbot=-ftop;
  
  // defining the matrix using given frustum definitions
  mat4 projmat;

  /*
    {2n/r-l, 0,      r+l/r-l, 0       }
    {0,      2n/t-b, t+b/t-b, 0       }
    {0,      0,      f+n/f-n, -2fn/f-n}
    {0,      0,      -1,      0       }
   */
  
  projmat.m[0][0]=(2*near)/(frig-flef);
  projmat.m[2][0]=(frig+flef)/(frig-flef);
  
  projmat.m[1][1]=(2*near)/(ftop-flef);
  projmat.m[2][1]=(ftop+fbot)/(ftop-fbot);

  projmat.m[2][2]=(far+near)/(far-near);
  projmat.m[3][2]=(-2*far*near)/(far-near);

  projmat.m[2][3]=1;

  return projmat;
  //return nsproj::identityMatrix();
}

nsproj::vec4 nsproj::vec4Xmat4(nsproj::vec4 a, nsproj::mat4 m){
  nsproj::vec4 ret;

  ret.x=(m.m[0][0]*a.x)+(m.m[1][0]*a.y)+(m.m[2][0]*a.z)+(m.m[3][0]*a.w);
  ret.y=(m.m[0][1]*a.x)+(m.m[1][1]*a.y)+(m.m[2][1]*a.z)+(m.m[3][1]*a.w);
  ret.z=(m.m[0][2]*a.x)+(m.m[1][2]*a.y)+(m.m[2][2]*a.z)+(m.m[3][2]*a.w);
  ret.w=(m.m[0][3]*a.x)+(m.m[1][3]*a.y)+(m.m[2][3]*a.z)+(m.m[3][3]*a.w);

  return ret;
}

nsproj::mat4 nsproj::modelMatrix(nsproj::vec3 rot, nsproj::vec3 tran, float s){
  nsproj::mat4 sc=nsproj::scaleMatrix({s,s,s});

  nsproj::mat4 roxy;
  nsproj::mat4 royz;
  nsproj::mat4 roxz;

  if(rot.x!=0){
    roxy=nsproj::rotateMatrixXY(rot.x);
  }

  if(rot.y!=0){
    royz=nsproj::rotateMatrixYZ(rot.y);
  }

  if(rot.z!=0){
    roxz=nsproj::rotateMatrixXZ(rot.z);
  }
  
  nsproj::mat4 ro=roxy*royz*roxz;

  nsproj::mat4 ret=sc*ro;

  ret.m[3][0]=tran.x;
  ret.m[3][1]=tran.y;
  ret.m[3][2]=tran.z;
  
  return ret;
}

nsproj::mat4 nsproj::viewMatrix(nsproj::vec3 up, nsproj::vec3 target, nsproj::vec3 tran){
  nsproj::vec3 right=nsproj::cross(up, target);
  right=nsproj::normalizeVec3(right);

  target=nsproj::cross(right, up);
  target=nsproj::normalizeVec3(target);
  
  nsproj::vec3 u=right;
  nsproj::vec3 v=up;
  nsproj::vec3 n=target;
  
  nsproj::mat4 view={
    {
      {u.x, u.y, u.z, -tran.x},
      {v.x, v.y, v.z, -tran.y},
      {n.x, n.y, n.z, -tran.z},
      {0,   0,   0,         1}
    }
  };

  return view;
}

nsproj::vec4 nsproj::operator*(const nsproj::vec4& a, const nsproj::mat4& m){
  return nsproj::vec4Xmat4(a, m);
}

nsproj::vec4& nsproj::operator*=(nsproj::vec4& a, const nsproj::mat4& m){
  a=nsproj::vec4Xmat4(a, m);

  return a;
}

nsproj::mat4 nsproj::operator*(const nsproj::mat4& a, const nsproj::mat4& m){
  return nsproj::multiplyMatrices(a, m);
}

nsproj::mat4& nsproj::operator*=(nsproj::mat4& a, const nsproj::mat4& m){
  a=nsproj::multiplyMatrices(a, m);

  return a;
}

void nsproj::debugOutputMatrix(mat4 m){
  for(int y=0; y<4; y++){
    for(int x=0; x<4; x++){
      std::cout << m.m[x][y] << ' ';
    }
    std::cout << std::endl;
  }
}

quat::quat(float pw, float pi, float pj, float pk):
  w(pw),
  i(pi),
  j(pj),
  k(pk){
  
}

quat quat::conjugate(){
  return quat(w, -i, -j, -k);
}

quat quat::normal(){
  return quat(w/norm(), i/norm(), j/norm(), k/norm());
}

quat quat::inverse(){
  return quat(conjugate().w/conjugateProduct(),
	      conjugate().i/conjugateProduct(),
	      conjugate().j/conjugateProduct(),
	      conjugate().k/conjugateProduct());
}

static quat quat::add(const quat& a, const quat& b){
  return quat(a.w+b.w, a.i+b.i, a.j+b.j, a.k+b.k);
}

static quat quat::subtract(const quat& a, const quat& b){
  return quat(a.w-b.w, -(a.i-b.i), -(a.j-b.j), -(a.k-b.k));
}

static quat quat::product(const quat& a, const quat& b){
  return quat(a.w*b.w-a.i*b.i-a.j*b.j-a.k*b.k,
	      (a.w*b.i+a.i*b.w+a.j*b.k-a.k*b.j),
	      (a.w*b.j+a.j*b.w+a.k*b.i-a.i*b.k),
	      (a.w*b.k+a.k*b.w+a.i*a.j-a.j*b.i));
}

static float quat::dotProduct(const quat& a, const quat&b){
  return (a.w*b.w+a.i*b.i+a.j*b.j+a.k*b.k);
}

float quat::conjugateProduct(){
  return (w*w+i*i+j*j+k*k);
}

float quat::norm(){
  return sqrt(w*w+i*i+j*j+k*k);
}
