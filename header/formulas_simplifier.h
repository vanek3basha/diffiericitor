#ifndef _SIMPLIFIER_
#define _SIMPLIFIER_

const double EPS = 10e-6;

struct tree* SimplifierTree(struct tree* root);

int iszero(double a);

#endif