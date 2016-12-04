LD_LIBRARY_PATH=/home1/04362/thuang/usr/local/lib
export LD_LIBRARY_PATH
g++ -o euler_gsl euler_gsl.cpp -I/home1/04362/thuang/usr/local/include -L/home1/04362/thuang/usr/local/lib -lgsl -lgslcblas
#g++ -o euler_gsl euler_gsl.cpp -I/home1/04362/thuang/usr/local/include -L/home1/04362/thuang/usr/local/lib -lgsl -lgsl_matrix_view_array -lgsl_matrix_set -lgsl_odeiv2_step_rk1imp -lgsl_odeiv2_driver_alloc_y_new -lgsl_odeiv2_driver_apply -lgsl_odeiv2_driver_free

