// Implentation of example 6. 
// This example works.
// The example can be found at:
//
//	https://www.kalmanfilter.net/kalman1d.html
//
// To build:
//
//	gcc -Wall example06.c
//
// To build:
//
//	./a.out

#include <stdio.h>

int main(void)
{
  // The measurements - range in metres.
  double z[10] = {49.95,49.967,50.1,50.106,49.992,49.819,49.933,50.007,50.023,49.99};	
  double x_n;		// current state.
  double p_n;		// current estimate uncertainty
  double temp_x_n_1;	
  double temp_p_n_1;
  double x_n_1;	
  double p_n_1;
  double sd;		// Standard deviation.
  double kalman_gain;
  double q;
  int iterations;
  
  iterations = 1;
  
  x_n    = x_n_1 = 10;		// Initial estimate of temperature.
  p_n    =         100;	        // Initial estimate of variance.
  sd     = 0.1;		        // altimeter measurement error (standard deviation).
  q      = 0.0001;  
   
  p_n_1  = p_n + q; 
   
  printf("Initial Estimations:\n"); 
  printf("x_n         = %f\n",x_n);
  printf("p_n         = %f\n",p_n);
  printf("\n");
 
  while (iterations < 11)
  {
    x_n_1 = x_n;
    p_n_1 = p_n;    

    
    kalman_gain = p_n / (p_n + (sd * sd));
    
    // Calculating the current estimate using the state update equation.
    temp_x_n_1 = x_n_1  + kalman_gain * (z[(iterations - 1)]  - x_n_1);
    temp_p_n_1 = (1 - kalman_gain) * p_n_1;
    
    // Calculating the next state estimate using the State Extrapolation Equations.
    x_n = temp_x_n_1;
    p_n = temp_p_n_1 + q;

    
    // Debug the values of the filter.
    printf("Intertion   = %d\n",iterations);
    printf("z[%2d]       = %f\n",iterations,z[(iterations - 1)]);
    printf("gain        = %f\n",kalman_gain);
    printf("x_n_1       = %f\n",x_n_1);
    printf("p_n_1       = %f\n",p_n_1);
    printf("temp_x_n_1  = %f\n",temp_x_n_1);
    printf("temp_p_n_1  = %f\n",temp_p_n_1);
    printf("x_n         = %f\n",x_n);
    printf("p_n         = %f\n",p_n);
    printf("\n");
    
    iterations++;
  }
  
  return 0;
}
