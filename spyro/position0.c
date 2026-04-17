#include <math.h>
#include "position.h".

void position(double t, double p[])
{
  p[0] = cos(t);
  p[1] = sin(t);
}
