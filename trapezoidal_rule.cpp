#include<iostream>
using namespace std;

double y(double x){
  return 1/x;
}

double trapezoidal(int n, double lower, double upper){
  double h=(upper-lower)/n;
  double result=0;
  for(double i = lower; i<=upper; i+=h){
    result += 2*y(i);
  }
  result -= (y(lower)+y(upper));
  result*=h/2;
  return result;
}

int main(){
  int n;
  double lower, upper;
  cout << "Lower limit of function?\n";
  cin >> lower;
  cout << "Upper limit of function?\n";
  cin >> upper;
  cout << "Number of iterations?\n";
  cin >> n;
  cout << "Value of the integral is: " << trapezoidal(n, lower, upper);
}
