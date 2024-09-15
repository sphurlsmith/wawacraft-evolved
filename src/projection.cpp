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

nsproj::mat4 nsproj::viewMatrix(nsproj::vec3 rot, nsproj::vec3 tran){
  nsproj::vec3 x={1,0,0};
  nsproj::vec3 y={0,1,0};
  nsproj::vec3 z={0,0,1};

  nsproj::mat4 hort=nsproj::rotateMatrixXZ(tran.x);
  nsproj::mat4 vert=nsproj::rotateMatrixYZ(tran.y);
  nsproj::mat4 lat=nsproj::rotateMatrixXY(tran.z);
  
  x=nsproj::normalizeVec4(nsproj::homogenizeVector(x)*hort);
  y=nsproj::normalizeVec4(nsproj::homogenizeVector(y));
  z=nsproj::normalizeVec4(nsproj::homogenizeVector(z)*hort);

  nsproj::mat4 view={
    {
      {x.x, y.x, z.x, -tran.x},
      {x.y, y.y, z.y, -tran.y},
      {x.z, y.z, z.z, -tran.z},
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
