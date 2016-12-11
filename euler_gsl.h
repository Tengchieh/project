//#include <stdio.h>
//#include <math.h>
//#include "gsl/gsl_errno.h"
//#include "gsl/gsl_matrix.h"
//#include "gsl/gsl_odeiv2.h"
//#include "option.h"

int func_simple(double t, const double y[], double f[], void *params);

//int jac_simple(double t, const double y[], double *dfdy, double dfdt[], void *params);

void SIMPLE_ODE_GSL(double step_size);

