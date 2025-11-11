#include <cmath>
#include <iostream>
using namespace std;

double y(double x) { return 2.4 * x * x * x + 4.4 * x * x - 2 * x + 1.5; }
double yprime(double x) {return 3*2.4*x*x+8.8*x-2;}

double secantmethod(double x0, double x1, double tolerance) {
  double x = x1;
  while (fabs(y(x)) > tolerance) {
    x = x1 - y(x1) * (x1 - x0) / (y(x1) - y(x0));
    x0 = x1;
    x1 = x;
  }
  return x;
}

double newtonRaphson(double x0, double tolerance){
    double x=x0;
    while(fabs(y(x))>tolerance){
      x=x0-(y(x0)/yprime(x0));
      x0=x;
    }
  return x;
}

int main() {
  int choice;
  cout << "Select the method to find roots of the function\n1. Secant "
          "Method\n2. Newton Raphson Method\n3. Bijection Method\nChoice: ";
  cin >> choice;
  if (choice == 1) {
    double x0, x1;
    cout << "Enter the first and second x values: ";
    cin >> x0 >> x1;
    double tolerance;
    cout << "Enter tolerance: ";
    cin >> tolerance;
    cout << "Solution of f(x) is x = " << secantmethod(x0, x1, tolerance);
    return 0;
  }
  if(choice==2){
    double x0, tolerance;
    cout<< "Enter inital guess for the root: ";
    cin >> x0;
    cout << "Enter tolerance for the solution: ";
    cin >> tolerance;
    cout << "The solution of f(x) is x = " << newtonRaphson(x0, tolerance);
  }
}
