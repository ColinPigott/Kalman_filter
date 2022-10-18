// Implentation of example 2. 
// This example works.
// The example can be found at:
//
//	https://www.kalmanfilter.net/alphabeta.html
//
// To build:
//
//	gcc -Wall example02.c
//
// To build:
//
//	./a.out

#include <stdio.h>

int main(void)
{
  // The measurements - range in metres.
  double z[10] = {30110,30265,30740,30750,31135,31015,31180,31610,31960,31865};	
  double x_n,xVel_n;			// The estimations.
  double temp_x_n_1,temp_xVel_n_1;	// The estimations.
  double x_n_1,xVel_n_1;		// The estimations.
  double gain_alpha,gain_beta;
  double time;
  int iterations;
  
  iterations = 1;
  gain_alpha = 0.2;
  gain_beta  = 0.1;
  time       = 5;	// Time between readings (in seconds).
  
  x_n    = x_n_1  = 30000;	// Position
  xVel_n = xVel_n_1 = 40;	// Velocity	
  
  
  // Work on the first estimation.
  x_n       = x_n + (xVel_n * time);
  xVel_n    = xVel_n;
 
  printf("Initial Estimations:\n"); 
  printf("x_n         = %f\n",x_n);
  printf("xVel_n      = %f\n",xVel_n);
  printf("\n");
 
  while (iterations < 11)
  {
    x_n_1 = x_n;
    xVel_n_1 = xVel_n;    
    
    // Calculating the current estimate using the state update equation.
    temp_x_n_1    = x_n_1  + gain_alpha * (z[(iterations - 1)]  - x_n_1);
    temp_xVel_n_1 = xVel_n_1 + gain_beta  * ((z[(iterations - 1)] - x_n_1) / time);
    
    // Calculating the next state estimate using the State Extrapolation Equations.
    x_n       = temp_x_n_1 + (temp_xVel_n_1 * time);
    xVel_n    = temp_xVel_n_1;
    
    // Debug the values of the filter.
    printf("Intertion   = %d\n",iterations);
    printf("z[%2d]       = %f\n",iterations,z[(iterations - 1)]);
    printf("time        = %f\n",time);
    printf("x_n_1       = %f\n",x_n_1);
    printf("x1_n_1      = %f\n",xVel_n_1);
    printf("temp_x_n_1  = %f\n",temp_x_n_1);
    printf("temp_x1_n_1 = %f\n",temp_xVel_n_1);
    printf("x_n         = %f\n",x_n);
    printf("x1_n        = %f\n",xVel_n);
    printf("\n");
    
    iterations++;
  }
  
  return 0;
}
