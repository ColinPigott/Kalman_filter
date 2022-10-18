// Implentation of the weight gold Kalman filter example. 
// This example works.
// The example can be found at:
//
//	https://www.kalmanfilter.net/alphabeta.html
//
// To build:
//
//	gcc -Wall example01.c
//
// To build:
//
//	./a.out
#include <stdio.h>

int main(void)
{
  // The measurements
  double z[10] = {1030,989,1017,1009,1013,979,1008,1042,1012,1011};	
  double x_n,x_n_1;	// The estimations.
  double gain;
  int iterations;
  
  iterations = 1;
  x_n = x_n_1 = 1000;
  
  while (iterations < 11)
  {
    x_n_1 = x_n;
    gain = 1 / (double)iterations;
    x_n  = x_n_1 + gain*(z[(iterations - 1)] - x_n_1);
    
    // Debug the values of the filter.
    printf("Intertion = %d\n",iterations);
    printf("x_n_1     = %f\n",x_n_1);
    printf("gain      = %f\n",gain);
    printf("x_n       = %f\n",x_n);
    printf("\n");
    
    iterations++;
  }
  
  return 0;
}
