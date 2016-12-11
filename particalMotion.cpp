
//  particalMotion.cpp
//  
//
//  Created by HUANGTENGCHIEH on 12/5/16.
//  x' = u
//  y' = v
//  z' = w
//  u' = w*v - u / tou
//  v' = -w*u - v / tou
//  w' = - w / tou
//  X0 = (x0,y0,z0) = (0,0,0)
//  v0 = X0'= (x0',y0',z0') =(20,0,2)
//

#include <stdio.h>
#include <math.h>
#include <iostream>
//#include <fstream>
#include "gsl/gsl_errno.h"
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_odeiv2.h"
#include "option.h"
#include "particalMotion.h"
using namespace std;

//int output_mode = 1;
//y = [x, y, z, u, v, w]; f = [x', y', z', u', v', w'];
int func_particle(double t, const double y[], double f[], void *params) {
    (void) (t);  /* avoid unused parameter warning */
    double mu = *(double *)params;
    f[0] = y[3];
    f[1] = y[4];
    f[2] = y[5];
    f[3] = mu * y[4] - y[3] / mu;
    f[4] = -mu * y[3] - y[4] / mu;
    f[5] = -y[5] / mu;
    return GSL_SUCCESS;
}
void jacobian_matrix_print(void)
{
	double matrix[6][6] = {{0.0, 0.0, 0.0, 1.0, 0.0, 0.0},
				{0.0, 0.0, 0.0, 0.0, 1.0, 0.0},
				{0.0, 0.0, 0.0, 0.0, 0.0, 1.0},
				{0.0, 0.0, 0.0, -0.2, 5.0, 0.0},
				{0.0, 0.0, 0.0, -5.0, -0.2, 0.0},
				{0.0, 0.0, 0.0, 0.0, 0.0, -0.2}};
	double dfdt[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	printf ("\nThe initial Jacobian matrix:\n");
	for (int i = 0; i < 6; i++){
                for (int j = 0; j < 6; j++){
                        printf ("m(%d,%d) = %f\n", i, j, matrix[i][j]);
                }
        }
	for (int i=0; i<6; i++)
                printf("df%d/dt = %f\n", i, dfdt[i]);
}
int flag_particle=0;
int jac_particle(double t, const double y[], double *dfdy, double dfdt[], void *params) {
    (void) (t);  /* avoid unused parameter warning */
    //double mu = *(double *)params;
    double mu = 5.0;
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 6, 6);
    gsl_matrix *m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, 0.0);
    gsl_matrix_set(m, 0, 1, 0.0);
    gsl_matrix_set(m, 0, 2, 0.0);
    gsl_matrix_set(m, 0, 3, 1.0);
    gsl_matrix_set(m, 0, 4, 0.0);
    gsl_matrix_set(m, 0, 5, 0.0);
    gsl_matrix_set(m, 1, 0, 0.0);
    gsl_matrix_set(m, 1, 1, 0.0);
    gsl_matrix_set(m, 1, 2, 0.0);
    gsl_matrix_set(m, 1, 3, 0.0);
    gsl_matrix_set(m, 1, 4, 1.0);
    gsl_matrix_set(m, 1, 5, 0.0);
    gsl_matrix_set(m, 2, 0, 0.0);
    gsl_matrix_set(m, 2, 1, 0.0);
    gsl_matrix_set(m, 2, 2, 0.0);
    gsl_matrix_set(m, 2, 3, 0.0);
    gsl_matrix_set(m, 2, 4, 0.0);
    gsl_matrix_set(m, 2, 5, 1.0);
    gsl_matrix_set(m, 3, 0, 0.0);
    gsl_matrix_set(m, 3, 1, 0.0);
    gsl_matrix_set(m, 3, 2, 0.0);
    gsl_matrix_set(m, 3, 3, -1.0/mu);
    gsl_matrix_set(m, 3, 4, mu);
    gsl_matrix_set(m, 3, 5, 0.0);
    gsl_matrix_set(m, 4, 0, 0.0);
    gsl_matrix_set(m, 4, 1, 0.0);
    gsl_matrix_set(m, 4, 2, 0.0);
    gsl_matrix_set(m, 4, 3, -mu);
    gsl_matrix_set(m, 4, 4, -1.0/mu);
    gsl_matrix_set(m, 4, 5, 0.0);
    gsl_matrix_set(m, 5, 0, 0.0);
    gsl_matrix_set(m, 5, 1, 0.0);
    gsl_matrix_set(m, 5, 2, 0.0);
    gsl_matrix_set(m, 5, 3, 0.0);
    gsl_matrix_set(m, 5, 4, 0.0);
    gsl_matrix_set(m, 5, 5, -1.0/mu);
    if(output_mode==2&&flag_particle==0){
	for (int i = 0; i < 6; i++){ 
    		for (int j = 0; j < 6; j++){
			printf ("\nThe initial Jacobian matrix:\n");
      			printf ("m(%d,%d) = %g\n", i, j, gsl_matrix_get (m, i, j));
		}
	}
    }
    dfdt[0] = 0.0;
    dfdt[1] = 0.0;
    dfdt[2] = 0.0;
    dfdt[3] = 0.0;
    dfdt[4] = 0.0;
    dfdt[5] = 0.0;
    if(output_mode==2&&flag_particle==0){
	for (int i=0; i<6; i++){
		printf("df%d/dt = %f\n", i, dfdt[i]);
	}
	flag_particle=1;
    }
    return GSL_SUCCESS;
}
void CHARGED_PARTICAL_MOTION(int method_sl,double step_size) {
    double mu = 5;
    const gsl_odeiv2_step_type* method; //gsl_odeiv2_step_rk4	gsl_odeiv2_step_rkf45 gsl_odeiv2_step_rk8pd
    if(method_sl==1)	method = gsl_odeiv2_step_rk4;
    else if(method_sl==2)	method = gsl_odeiv2_step_rk8pd;
    else	method = gsl_odeiv2_step_rk1imp;
    gsl_odeiv2_system sys = { func_particle, jac_particle, 6, &mu };
    gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, method, 1e-6, 1e-6, 0.0);
    
    int i;
    double t = 0.0, t1 = 5.0;
    const double x0 = 0.0;
    const double y0 = 0.0;
    const double z0 = 0.0;
    const double u0 = 20.0;
    const double v0 = 0.0;
    const double w0 = 2.0;
    double y[6] = {x0, y0, z0, u0, v0, w0};
    const int N = t1/step_size;
    printf("time\t \t(x, \t\ty, \t\tz\t)");
    if(vf_mode==1) printf("\tanalytical sol(x, y, \t\tz ) \t\terror norm");
    printf("\n");

    //ofstream file;
    //file.open("p2m%d_traj.dat",method_sl);
    for (i = 0; i <= N; i++) {
        double ti = i * step_size;
        int status = gsl_odeiv2_driver_apply(d, &t, ti, y);
	//int status = gsl_odeiv2_driver_apply_fixed_step(d, &t, 5e-2, 100, y);
	double ana_x = 50./313. * exp(-1*t/5) * (exp(t/5) - cos(5*t) + 25*sin(5*t) );
	double ana_y = -50./313. * exp(-1*t/5) * (25*exp(t/5) - 25*cos(5*t) -sin(5*t) );
	double ana_z = 10*exp(-1*t/5) * (-1 + exp(t/5) );
        if (status != GSL_SUCCESS) {
            printf("error, return value=%d\n", status);
            break;
        }
	if(i==1&&output_mode==2){
		if(method_sl!=3)   jacobian_matrix_print();
		printf("\ntime\t \t(x, \t\ty, \t\tz\t)");   
		if(vf_mode==1) 	printf("\tanalytical sol(x, y, \t\tz ) \t\terror norm");
		printf("\n");
	}
        printf("%.5e\t%.5e\t%.5e\t%.5e\t", t, y[0], y[1], y[2]);
	//file << y[0] << " " << y[1] << " " << y[2] << endl;
	if(vf_mode==1)	printf("%.5e\t%.5e\t%.5e\t%.5e", ana_x, ana_y, ana_z, sqrt(pow(ana_x-y[0],2)+pow(ana_y-y[1],2)+pow(ana_z-y[2],2)));
	printf("\n");
    }
    //file.close();
    gsl_odeiv2_driver_free(d);
    printf("\n...and done!\n");
}

