#include <stdio.h>
#include <math.h>
#include "lib/gsl/gsl_errno.h"
#include "lib/gsl/gsl_matrix.h"
#include "lib/gsl/gsl_odeiv2.h"
//The code is to solve y'(t) = t*y(t)

int func(double t, const double y[], double f[], void *params) {
    f[0] = -t* y[0];
    return GSL_SUCCESS;
}
int jac(double t, const double y[], double *dfdy, double dfdt[], void *params) {
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 1, 1);
    gsl_matrix *m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, -t);
    dfdt[0] = -1;
    return GSL_SUCCESS;
}
int main(void) {
    double mu = 0;
    gsl_odeiv2_system sys = { func, jac, 1, &mu };
    gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys,gsl_odeiv2_step_rk1imp, 1e-7, 1e-7, 0.0);
    int i;
    double t = 0.0, t1 = 2.0;
    const double x0 = 1.0;
    double y[1] = {x0};
    const int N = 100;
    printf("time\t \tapprox solution \t exact solution\n");
    for (i = 0; i <= N; i++) {
        double ti = i * (t1 / N);
        int status = gsl_odeiv2_driver_apply(d, &t, ti, y);
        if (status != GSL_SUCCESS) {
            printf("error, return value=%d\n", status);
            break;
        }
        printf("%.5e\t%.5e\t\t%.5e\n", t, y[0], x0*exp(-0.5*t*t));
    }
    gsl_odeiv2_driver_free(d);
    printf("\n...and done!\n");
    return 0;
}

