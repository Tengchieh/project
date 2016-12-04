#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;
typedef double F(double,double);

/*
 * Approximates y(t) in y'(t)=f(t,y) with y(a)=y0 and
 * t=a..b and the step size h.
 * */
void euler(F f, double y0, double start_time, double end_time, double step_size)
{
	double y = y0;
	cout << "time" << "\t\t" << "approx solution" << "\t\t" << "exact solution" << endl;
	for (double t = start_time; t <= end_time; t += step_size)
	{
		cout << scientific << setprecision(5) << t << "\t" << y << "\t" << exp(-0.5*t*t) <<  endl;
		y += step_size * f(t, y);
	}
	cout << "done" << endl;
}

// Example: Newton's cooling law
/*double newtonCoolingLaw(double, double y)
{
	return -0.07 * (y - 20);
}*/
double simpleODE(double t, double y)
{
	return -t * y;
}

int main()
{
	euler(simpleODE, 1, 0, 2.02,  0.02);
}
