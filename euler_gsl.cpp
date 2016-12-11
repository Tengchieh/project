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

//class jac_simple_holder
//{
//	gsl_matrix *m = &dfdy_mat.matrix;
//public:	
//	int jac_simple();
//	void debugger();
//};
int flag_simple=0;
int jac_simple(double t, const double y[], double *dfdy, double dfdt[], void *params) {
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 1, 1);
    gsl_matrix *m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, -t);
   if(output_mode==2&&flag_simple==0){
	 for (int i = 0; i < 1; i++){  /* OUT OF RANGE ERROR */
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

//void jac_simple_holder::debugger(){
	//if(output_mode==2){
//		for (int i = 0; i < 1; i++){  /* OUT OF RANGE ERROR */
 //               	for (int j = 0; j < 1; j++){
  //                      	printf ("The Jacobian matrix is :\n");
   //                     	printf ("m(%d,%d) = %g\n", i, j, gsl_matrix_get (m, i, j));
    //            	}
     //   	}
//		printf("\ndf/dt = %f\n", dfdt[0]);
    	//}
//}
void SIMPLE_ODE_GSL(double step_size) {
    //output_mode = o_mode;
    int mu = 0;
    gsl_odeiv2_system sys = { func_simple, jac_simple, 1, &mu };
    gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys,gsl_odeiv2_step_rk1imp, 1e-7, 1e-7, 0.0);
    int i;
    double t = 0.0, t1 = 2.0;
    const double x0 = 1.0;
    double y[1] = {x0};
    const int N = t1/step_size;

    printf("time\t \tapprox solution \t exact solution\n");
    for (i = 0; i <= N; i++) {
        double ti = i * step_size;
        int status = gsl_odeiv2_driver_apply(d, &t, ti, y);
        if (status != GSL_SUCCESS) {
            printf("error, return value=%d\n", status);
            break;
        }
	if(output_mode==2&&i==1)	printf("\ntime\t \tapprox solution \t exact solution\n");
        printf("%.5e\t%.5e\t\t%.5e\n", t, y[0], x0*exp(-0.5*t*t));
    }
    gsl_odeiv2_driver_free(d);
    printf("\n...and done!\n");
}

