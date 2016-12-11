#include <stdio.h>
#include <math.h>
#include "gsl/gsl_errno.h"
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_odeiv2.h"
#include "option.h"
#include "euler_gsl.h"
//The code is to solve y'(t) = t*y(t)
//int output_mode;

int func_simple(double t, const double y[], double f[], void *params) {
    f[0] = -t* y[0];
    return GSL_SUCCESS;
}

int flag_simple=0;
int jac_simple(double t, const double y[], double *dfdy, double dfdt[], void *params) {
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 1, 1);
    gsl_matrix *m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, -t);
   if(output_mode==2&&flag_simple==0){
	 for (int i = 0; i < 1; i++){  
   		for (int j = 0; j < 1; j++){
			printf ("\nThe initial Jacobian matrix is :\n");
      			printf ("m(%d,%d) = %g\n", i, j, gsl_matrix_get (m, i, j));
		}
	}
    }
    dfdt[0] = -1;
    if(output_mode==2&&flag_simple==0){
	printf("df/dt = %f\n", dfdt[0]);
	flag_simple=1;
    }
    return GSL_SUCCESS;
}

void SIMPLE_ODE_GSL(double step_size) {
    int mu = 0;
    gsl_odeiv2_system sys = { func_simple, jac_simple, 1, &mu };
    gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys,gsl_odeiv2_step_rk1imp, 1e-7, 1e-7, 0.0);
    int i;
    double t = 0.0, t1 = 2.0;
    const double x0 = 1.0;
    double y[1] = {x0};
    const int N = t1/step_size;

    printf("\ntime\t \tnumerical sol \t");
    if(vf_mode==1) printf("analytical sol\terror \%\n");

    for (i = 0; i <= N; i++) {
        double ti = i * step_size;
	double ana_sol=x0*exp(-0.5*t*t);
        int status = gsl_odeiv2_driver_apply(d, &t, ti, y);
        if (status != GSL_SUCCESS) {
            printf("error, return value=%d\n", status);
            break;
        }
	if(i==1){
		if(output_mode==2)	printf("\ntime\t \tnumerical sol \t");
		if(vf_mode==1) printf("analytical sol\terror \%");
		if(output_mode==2||vf_mode==1) printf("\n");
	}
        printf("%.5e\t%.5e\t", t, y[0]);
	if(vf_mode==1) printf("%.5e\t%.5e", ana_sol, (ana_sol-y[0])/ana_sol);
	printf("\n");
    }
    gsl_odeiv2_driver_free(d);
    printf("\n...and done!\n");
}

