//
//  run.c
//  
//
//  Created by HUANGTENGCHIEH on 12/8/16.
//
// libGRVY - a utility library for scientific computing.
//
// C example illustrating basic input file parsing via libGRVY.
//
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <grvy.h>
//#include "euler.h"
//#include "euler_gsl.h"
//#include "particalMotion.h"

int main(int argc, char **argv)
{
    int igot;
    int problem, method;
    float step_size;
    int vf_mode;
    int output_mode;
    /* Initialize/read the file */
    
    igot = grvy_input_fopen("./input.dat");
    
    /* Read specific variables and echo locally */
    
    if(grvy_input_fread_int("problem",&problem))
        printf("--> %-10s = %i\n","problem", problem);
    
    if(grvy_input_fread_int("method",&method))
        printf("--> %-10s = %i\n","method", method);
    
    if(grvy_input_fread_float("step_size",&step_size))
        printf("--> %-10s = %f\n","step_size", step_size);
    
    if(grvy_input_fread_int("vf_mode",&vf_mode))
        printf("--> %-10s = %i\n","vf_mode", vf_mode);
    
    if(grvy_input_fread_int("output_mode",&output_mode))
        printf("--> %-10s = %i\n","output_mode", output_mode);

    if(problem==1){
        if(method==1)   SIMPLE_ODE_FORWARD(step_size, vf_mode, output_mode);
        else if(method==2)  SIMPLE_ODE_GSL(step_size, vf_mode, output_mode);
        else    printf("Choose wrong method number, please select 1  or 2.\n");
    }else if(problem==2){
	if(method>3){	
		printf("Choose wrong method number, please select 1 to 3.\n")
		break;
        else CHARGED_PARTICAL_MOTION(method, step_size, vf_mode, output_mode);
    }else   printf("Choose wrong problem number, please select 1  or 2\n");
    
    
    
    /* Close the file */
    
    grvy_input_fclose();
    
    return 0;
}
