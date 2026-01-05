#include "header/sravnenie.h"
#include <math.h>

bool CompareFloats(double a, double b) 
{
    const double EPSILON = 10e-5;
    return fabs(a - b) < EPSILON;
}