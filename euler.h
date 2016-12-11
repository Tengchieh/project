//#include <iomanip>
//#include <iostream>
//#include <math.h>
//#include "option.h"
using namespace std;
typedef double F(double,double);

void euler(F f, double y0, double start_time, double end_time, double step_size, int o_mode);

double simpleODE(double t, double y);

void SIMPLE_ODE_FORWARD(double step_size);

