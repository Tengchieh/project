#include <stdio.h>
#include <math.h>
#include "gsl/gsl_errno.h"
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_odeiv2.h"
using namespace std;

int func(double t, const double y[], double f[], void *params);

int jac(double t, const double y[], double *dfdy, double dfdt[], void *params);

void CHARGED_PARTICAL_MOTION(int m,double step_size,int vf_mode,int output_mode);
