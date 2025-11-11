#include <iostream>
using namespace std;

double y(double x) { return 1 / x; }

double simpson38(int n, double lower, double upper) {
  double h = (upper - lower) / n;
  double result = 0;
  int counter = 0;
  for (double i = lower; i <= upper; i += h) {
    if (counter % 3) {
      result += 3 * y(i);
    } else {
      result += 2 * y(i);
    }
    counter++;
  }
  result -= (y(lower)+y(upper));
  result *= 3*h/8;
  return result;
}

int main(){
  int n;
  double upper, lower;
  cout << "Lower limit of function?\n";
  cin >> lower;
  cout << "Upper limit of function?\n";
  cin >> upper;
  cout << "Number of iterations?\n";
  cin >> n;
  cout << "The value of integral is: " << simpson38(n, lower, upper);
}
