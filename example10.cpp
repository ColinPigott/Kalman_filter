// Implentation of example 10.  
// 
// The example can be found at:
//
//	https://www.kalmanfilter.net/multiExamples.html
//
// To build:
//  g++ -Wall -I /home/linuxbox/eigen-3.4.0 example10.cpp
//
// N.B. eigen has to be installed first before this example will work.
//
// To build:
//
//	./a.out

#include <iostream>
#include <Eigen/Dense>
 
using Eigen::MatrixXd;
using namespace std;
 
int main()
{
  MatrixXd f(2,2),g(2,1),q(2,2),h(1,2),k(2,1),r(1,1),p_n(2,2),p_n_1(2,2),p_n_2(2,2),p_n_3(2,2),x_n(2,1),x_n_1(2,1),x_n_2(2,1),z_n(1,1),i;
  double delta_t,var_x,u_n,e_sd;
  const double gravity = 9.8;

  double z[] = { -32.40, -11.10,  18.00,  22.90,  19.50,  28.50,  46.50,  68.90,  48.20,  56.10,  90.50, 104.90, 140.90, 148.00, 187.60, 209.20, 244.60, 276.40, 323.50, 357.30, 357.40, 398.30, 446.70, 465.10, 529.40, 570.40, 636.80, 693.30, 707.30, 748.35};
  double u[] = {  39.72,  40.02,  39.97,  39.81,  39.75,  39.60,  39.77,  39.83,  39.73,  39.87,  39.81,  39.92,  39.78,  39.98,  39.76,  39.86,  39.61,  39.86,  39.74,  39.87,  39.63,  39.67,  39.96,  39.80,  39.89,  39.85,  39.90,  39.81,  39.81,  39.68};
  int iteration = 0;

  delta_t = 0.25;
  var_x = 20.0;
  e_sd  = 0.1;

  // Setup a 6x6 identity matrix.
  i = MatrixXd::Identity(2,2);
  
  // Setup the state transition matrix F.
  f(0,0) = 1.0; 
  f(1,0) = 0.0;
  
  f(0,1) = delta_t;
  f(1,1) = 1.0;

  // Setup the g matrix
  g(0,0) = 0.5 * (delta_t * delta_t);
  g(1,0) = delta_t;

  // Setup the process noise matrix Q.
  q(0,0) = (delta_t * delta_t * delta_t * delta_t) / 4.0;
  q(1,0) = (delta_t * delta_t * delta_t) / 2.0;
  
  q(0,1) = (delta_t * delta_t * delta_t) / 2.0;
  q(1,1) = delta_t * delta_t;

  q = q * (e_sd * e_sd);

  // Setup the measurement uncertainty matrix R.
  r(0,0) = var_x * var_x;

  // Setup the observation matrix H.
  h(0,0) = 1.0;
  h(0,1) = 0.0;

  cout << "state transition matrix F:" << endl;
  cout << f << endl;
  
  cout << "process noise matrix Q:" << endl;
  cout << q << endl;
  
  cout << "observation matrix H:" << endl;
  cout << h << endl;
  
  cout << "measurement uncertainty matrix R:" << endl;
  cout << r << endl;


 // Initialise
 x_n.setZero();

 // Initalize the process noise matrix P.
 p_n.setZero();
 p_n(0,0) = 500.0;
 p_n(1,1) = 500.0;

 u_n = gravity;

 // Interation zero.
 x_n = (f * x_n) + g * u_n;
 p_n = (f * p_n *f.transpose()) + q;

 // +++++ debug
 cout << "Interation0:" << endl;
 cout << "x_n:"  << endl;
 cout << x_n << endl;
 cout << "p_n:" << endl;
 cout << p_n << endl;

 while (iteration < 30)
 {
   cout << "Iteration = " << (iteration + 1) << endl;

   // Obtain the measurements.
   z_n(0,0) = z[iteration];
   u_n      = u[iteration];

   // +++++ Debug
   cout << "measurements z:" << endl;
   cout << z_n << endl;
   cout << u_n << endl;

   cout << "state metrix:" << endl;
   cout << x_n << endl;

   cout << "process noise matrix:" << endl;
   cout << p_n << endl;

   // Update the gain
   k = (p_n * h.transpose()) * (((h*p_n*h.transpose()) + r).inverse());

   // +++++ debug
   cout << "Kalman gain:" << endl;
   cout << k << endl;

   // Estimate the current state.
   x_n_1 = x_n + k * (z_n-h*x_n);

   // +++++ Debug
   cout << "x_n_1:" << endl;
   cout << x_n_1 << endl;

   // Estimate the current estimate uncertainty.
   p_n_1 = (i-k*h)*p_n*((i-k*h)).transpose()+(k*r*k.transpose());

   // +++++ Debug
   cout << "p_n_1:" << endl;
   cout << p_n_1 << endl;

   // Predict.
   x_n_2 = (f*x_n_1) + g * (u_n - gravity);

   p_n_2 = (f * p_n_1 * f.transpose()) + q;

   // +++++ Debug
   cout << "x_n_2:" << endl;
   cout << x_n_2 << endl;

   cout << "p_n_2:" << endl;
   cout << p_n_2 << endl;
   cout << endl;

   // Ready for the next iteration.
   iteration++;
   p_n = p_n_2;
   x_n = x_n_2;
 }

  
}
