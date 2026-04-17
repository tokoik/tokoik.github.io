#include <math.h>

void position(double t, double p[])
{
  p[0] = cos(5.0 * t + 1.0);
  p[1] = sin(3.0 * t);
}
