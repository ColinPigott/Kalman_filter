// Implentation of example 9. 
// 
// The example can be found at:
//
//	https://www.kalmanfilter.net/multiExamples.html
//
// To build:
//  g++ -Wall -I /home/linuxbox/eigen-3.4.0 example09.cpp
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
  MatrixXd f(6,6),q(6,6),h(2,6),k(6,2),r(2,2),p_n(6,6),p_n_1(6,6),p_n_2(6,6),p_n_3(6,6),x_n(6,1),x_n_1(6,1),x_n_2(6,1),z(2,1),i;
  double delta_t,var_a,var_x,var_y;

  double z_x[] = {-393.66,-375.93,-351.04,-328.96,-299.35,-273.36,-245.89,-222.58,-198.03,-174.17,-146.32,-123.72,-103.47,-78.23,-52.63,-23.34, 25.96, 49.72, 76.94, 95.38,119.83,144.01,161.84,180.56,201.42,222.62,239.4,252.51,266.26,271.75,277.4 ,294.12,301.23,291.8 ,299.89};
  double z_y[] = { 300.4,  301.78, 295.1,  305.19, 301.06, 302.05, 300.0,  303.57, 296.33, 297.65, 297.41, 299.61, 299.6, 302.39,295.04,300.09,294.72,298.61,294.64,284.88,272.82,264.93,251.46,241.27,222.98,203.73,184.1,166.12,138.71,119.71,100.41, 79.76, 50.62, 32.99,  2.14};
  int iteration = 0;

  delta_t = 1.0;
  var_a   = 0.2;
  var_x   = 3.0;
  var_y   = 3.0;

  // Setup a 6x6 identity matrix.
  i = MatrixXd::Identity(6,6);
  
  // Setup the state transition matrix F.
  f(0,0) = 1.0; 
  f(1,0) = 0.0;
  f(2,0) = 0.0;
  f(3,0) = 0.0;
  f(4,0) = 0.0;
  f(5,0) = 0.0;
  
  f(0,1) = delta_t;
  f(1,1) = 1.0;
  f(2,1) = 0.0;
  f(3,1) = 0.0;
  f(4,1) = 0.0;
  f(5,1) = 0.0;
  
  f(0,2) = 0.5 * (delta_t * delta_t);
  f(1,2) = delta_t;
  f(2,2) = 1.0;
  f(3,2) = 0.0;
  f(4,2) = 0.0;
  f(5,2) = 0.0;
  
  f(0,3) = 0.0;
  f(1,3) = 0.0;
  f(2,3) = 0.0;
  f(3,3) = 1.0;
  f(4,3) = 0.0;
  f(5,3) = 0.0;
  
  f(0,4) = 0.0;
  f(1,4) = 0.0;
  f(2,4) = 0.0;
  f(3,4) = delta_t;
  f(4,4) = 1.0;
  f(5,4) = 0.0;
  
  f(0,5) = 0.0;
  f(1,5) = 0.0;
  f(2,5) = 0.0;
  f(3,5) = 0.5 * (delta_t * delta_t);
  f(4,5) = delta_t;
  f(5,5) = 1.0;

  // Setup the process noise matrix Q.
  q(0,0) = (delta_t * delta_t * delta_t * delta_t) / 4.0;
  q(1,0) = (delta_t * delta_t * delta_t) / 2.0;
  q(2,0) = (delta_t * delta_t) / 2.0;
  q(3,0) = 0.0;
  q(4,0) = 0.0;
  q(5,0) = 0.0;
  
  q(0,1) = (delta_t * delta_t * delta_t) / 2.0;
  q(1,1) = delta_t * delta_t;
  q(2,1) = delta_t;
  q(3,1) = 0.0;
  q(4,1) = 0.0;
  q(5,1) = 0.0;

  q(0,2) = (delta_t * delta_t) / 2.0;
  q(1,2) = delta_t;
  q(2,2) = 1.0;
  q(3,2) = 0.0;
  q(4,2) = 0.0;
  q(5,2) = 0.0;
  
  q(0,3) = 0.0;
  q(1,3) = 0.0;
  q(2,3) = 0.0;
  q(3,3) = (delta_t * delta_t * delta_t * delta_t) / 4.0;
  q(4,3) = (delta_t * delta_t * delta_t) / 2.0;
  q(5,3) = (delta_t * delta_t) / 2.0;
  
  q(0,4) = 0.0;
  q(1,4) = 0.0;
  q(2,4) = 0.0;
  q(3,4) = (delta_t * delta_t * delta_t) / 2.0;
  q(4,4) = delta_t * delta_t;
  q(5,4) = delta_t;
  
  q(0,5) = 0.0;
  q(1,5) = 0.0;
  q(2,5) = 0.0;
  q(3,5) = (delta_t * delta_t) / 2.0;
  q(4,5) = delta_t;
  q(5,5) = 1.0;

  q = q * var_a;

  // Setup the measurement uncertainty matrix R.
  r(0,0) = var_x * var_x;
  r(1,0) = 0.0;
  
  r(0,1) = 0.0;
  r(1,1) = var_y * var_y;
  
  // Setup the observation matrix H.
  h(0,0) = 1.0;
  h(1,0) = 0.0;
  
  h(0,1) = 0.0;
  h(1,1) = 0.0;
  
  h(0,2) = 0.0;
  h(1,2) = 0.0;
  
  h(0,3) = 0.0;
  h(1,3) = 1.0;
  
  h(0,4) = 0.0;
  h(1,4) = 0.0;
  
  h(0,5) = 0.0;
  h(1,5) = 0.0;

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
 p_n(2,2) = 500.0;
 p_n(3,3) = 500.0;
 p_n(4,4) = 500.0;
 p_n(5,5) = 500.0;

 // Interation zero.
 x_n = f * x_n;
 p_n = (f * p_n *f.transpose()) + q;

 while (iteration < 35)
 {
   cout << "Iteration = " << (iteration + 1) << endl;

   // Obtain the measurements.
   z(0,0) = z_x[iteration];
   z(1,0) = z_y[iteration];

   // +++++ Debug
   cout << "measurements z:" << endl;
   cout << z << endl;

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
   x_n_1 = x_n + k * (z-h*x_n);

   // +++++ Debug
   cout << "x_n_1:" << endl;
   cout << x_n_1 << endl;

   // Estimate the current estimate uncertainty.
   p_n_1 = (i-k*h)*p_n*((i-k*h)).transpose()+(k*r*k.transpose());

   // +++++ Debug
   cout << "p_n_1:" << endl;
   cout << p_n_1 << endl;

   // Predict.
   x_n_2 = f*x_n_1;

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
