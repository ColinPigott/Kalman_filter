// Implentation of the alpha_beta_gamma filter example. 
// This example works.
// The example can be found at:
//
//	https://www.kalmanfilter.net/alphabeta.html
//
// To build:
//
//	gcc -Wall alpha_beta_gamma.c
//
// To build:
//
//	./a.out

#include <stdio.h>

int main(void)
{
  // The measurements - range in metres.
  double z[10] = {30160,30365,30890,31050,31785,32215,33130,34510,36010,37265};	
  double x_n,x1_n,x2_n;			// The estimations.
  double temp_x_n_1,temp_x1_n_1,temp_x2_n_1;	// The estimations.
  double x_n_1,x1_n_1,x2_n_1;			// The estimations.
  double gain_alpha,gain_beta,gain_gamma;
  double time;
  int iterations;
  
  iterations = 1;
  gain_alpha = 0.5;
  gain_beta  = 0.4;
  gain_gamma = 0.1;
  time       = 5;	// Time between readings (in seconds).
  
  x_n  = x_n_1  = 30000;
  x1_n = x1_n_1 = 50;
  x2_n = x2_n_1 = 0;
  
  
  // Work on the first estimation.
  x_n       = x_n + (x1_n * time) + x2_n * ((time*time) / 2);
  x1_n      = x1_n + (x2_n * time);
  x2_n      = x2_n;
 
  printf("Estimations:\n"); 
  printf("x_n         = %f\n",x_n);
  printf("x1_n        = %f\n",x1_n);
  printf("x2_n        = %f\n",x2_n);
  printf("\n");
  
  while (iterations < 11)
  {
    x_n_1 = x_n;
    x1_n_1 = x1_n;    
    x2_n_1 = x2_n;
    
    // Calculating the current estimate using the state update equation.
    temp_x_n_1  = x_n_1  + gain_alpha * (z[(iterations - 1)]  - x_n_1);
    temp_x1_n_1 = x1_n_1 + gain_beta  * ((z[(iterations - 1)] - x_n_1) / time);
    temp_x2_n_1 = x2_n_1 + gain_gamma * ((z[(iterations - 1)] - x_n_1) / (0.5 * (time * time)));
    
    // Calculating the next state estimate using the State Extrapolation Equations.
    x_n       = temp_x_n_1 + temp_x1_n_1 * time + temp_x2_n_1 * ((time*time) / 2);
    x1_n      = temp_x1_n_1 + temp_x2_n_1 * time;
    x2_n      = temp_x2_n_1;
    
    // Debug the values of the filter.
    printf("Intertion   = %d\n",iterations);
    printf("time        = %f\n",time);
    printf("x_n_1       = %f\n",x_n_1);
    printf("x1_n_1      = %f\n",x1_n_1);
    printf("x2_n_1      = %f\n",x2_n_1);
    printf("temp_x_n_1  = %f\n",temp_x_n_1);
    printf("temp_x1_n_1 = %f\n",temp_x1_n_1);
    printf("temp_x2_n_1 = %f\n",temp_x2_n_1);
    printf("x_n         = %f\n",x_n);
    printf("x1_n        = %f\n",x1_n);
    printf("x2_n        = %f\n",x2_n);
    printf("\n");
    
    iterations++;
  }
 
  return 0;
}
