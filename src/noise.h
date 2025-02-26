#ifndef NOISE_H
#define NOISE_H

#include "libs.h"
#include "mathlib.h"

struct noiseunit{
  int x;
  int y;
  
  vector corners[4];
};

class perlin
{
 public:
  perlin(double pgrid_size, int pgx, int pgy);

  static double interpolate(double x0, double y0, double x1, double y1, double x);

  void resize(double psize);
  
  void influence_generate(int px, int py);
  void influences_generate();
  
  int influence_find(int px, int py);
  
  double get(double x, double y);
  
 private:
  int grid_width;
  int grid_height;
  
  double grid_size;
  
  std::vector<noiseunit> influences;
};

#endif
