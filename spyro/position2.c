#include <math.h>

void position(double t, double p[])
{
  p[0] = 1.0 * cos(3 * t) + 0.5 * cos(5 * t);
  p[1] = 1.0 * sin(3 * t) + 0.5 * sin(5 * t);
}
