#include "libs.h"
#include "mathlib.h"
#include "noise.h"

perlin::perlin(double pgrid_size, int pgx, int pgy):
  grid_width(pgx),
  grid_height(pgy),
  grid_size(pgrid_size){
  influences.reserve(grid_width*grid_height);
  influences_generate();
}

static double perlin::interpolate(double x0, double y0, double x1, double y1, double x)
{
  return (y0+((x-x0)*(y1-y0)/(x1-x0)));
}

void perlin::resize(double psize)
{
  grid_size=psize;
}

void perlin::influence_generate(int px, int py)
{
  if(px<grid_width && py<grid_height){
    double angle;

    for(int x=0; x<4; x++){
      angle=fmod(rand(), (2*MATHLIB_PI));

      influences[influence_find(px, py)].x=px;
      influences[influence_find(px, py)].y=py;
      
      influences[influence_find(px, py)].corners[x].x=(cos(angle));
      influences[influence_find(px, py)].corners[x].y=(sin(angle));
    }
  }else{
    std::cerr << "err:w-perlin-influence_generate-request_out_of_bounds" << std::endl;
  }
}

void perlin::influences_generate()
{
  for(int y=0; y<grid_height; y++){
    for(int x=0; x<grid_width; x++){
      int i=x+y*grid_width;
      double angle;

      for(int z=0; z<4; z++){
	angle=fmod(rand(), (2*MATHLIB_PI));
	
	influences[i].x=x;
	influences[i].y=y;
	
	influences[i].corners[z].x=(cos(angle));
	influences[i].corners[z].y=(sin(angle));
      }
    }
  }
}

int perlin::influence_find(int px, int py)
{
  if(px<grid_width && py<grid_height){
    for(int x=0; x<influences.size(); x++){
      if(influences[x].x==px && influences[x].y==py){
	return x;
      }
    }
  }else{
    std::cerr << "err:w-perlin-influence_find-request_out_of_bounds" << std::endl;
  }

  return -1;
}

double perlin::get(double x, double y)
{
  x=(fmod(x, grid_width));
  y=(fmod(x, grid_height));

  vector xy(x, y);

  noiseunit unit=influences[influence_find(x, y)];
  
  vector tx0y0=vector::subtract(xy, vector(0, 0));
  vector tx1y0=vector::subtract(xy, vector(1*grid_width, 0));
  vector tx0y1=vector::subtract(xy, vector(0, 1*grid_height));
  vector tx1y1=vector::subtract(xy, vector(1*grid_width, 1*grid_height));

  double zx0y0=vector::dot_sum(unit.corners[0], tx0y0);
  double zx1y0=vector::dot_sum(unit.corners[1], tx1y0);
  double zx0y1=vector::dot_sum(unit.corners[2], tx0y1);
  double zx1y1=vector::dot_sum(unit.corners[3], tx1y1);

  double zxy=perlin::interpolate(0,
				 perlin::interpolate(0, zx0y0, 1, zx1y0, x/grid_width),
				 1,
				 perlin::interpolate(0, zx0y1, 1, zx1y1, x/grid_width),
				 y/grid_height);
  
  return zxy;
}
