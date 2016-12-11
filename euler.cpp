#include <iomanip>
#include <iostream>
#include <math.h>
#include "euler.h"
#include "option.h"
using namespace std;
typedef double F(double,double);

/*
 * Approximates y(t) in y'(t)=f(t,y) with y(a)=y0 and
 * t=a..b and the step size h.
 * */

void euler(F f, double y0, double start_time, double end_time, double step_size)
{
	double y = y0;
	cout << "time" << "\t\t" << "numerical" << "\t";
	if(vf_mode==1) cout << "analytical" << " " << "error norm" << " " << "error \%"; 
	cout << endl;
	for (double t = start_time; t <= end_time; t += step_size)
	{
		double ana_sol = exp(-0.5*t*t);
		cout << scientific << setprecision(5) << t << "\t" << y << "\t";
		if(vf_mode==1) cout << scientific << setprecision(5) << ana_sol << " " << (ana_sol-y) << " " << (ana_sol-y)/ana_sol;
		if(output_mode==2) cout << "    " << "f(t, y)= " << f(t,y);
		cout<<endl;
		y += step_size * f(t, y);
	}
	cout << "done" << endl;
}

double simpleODE(double t, double y)
{
	return -t * y;
}

void SIMPLE_ODE_FORWARD(double step_size)
{
	euler(simpleODE, 1, 0, 2.02, step_size);
}
