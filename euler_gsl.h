#include <stdio.h>
#include <math.h>
#include "lib/gsl/gsl_errno.h"
#include "lib/gsl/gsl_matrix.h"
#include "lib/gsl/gsl_odeiv2.h"

int output_mode;

int func(double t, const double y[], double f[], void *params);

int jac(double t, const double y[], double *dfdy, double dfdt[], void *params);

void SIMPLE_ODE_GSL(double step_size, int v_mode, int o_mode);

