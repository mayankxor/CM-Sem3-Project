#include<iostream>
using namespace std;

double y(double x){
  return 1/x;
}

double simpson13(int n, double lower, double upper){
  double h=(upper-lower)/n;
  int counter=0;
  double result=0;
  for(double i = lower; i<=upper; i+=h){
    if (counter%2){result+=4*y(i);}
    else{result+=2*y(i);}
    counter++;
  }
  result-=(y(lower)+y(upper));
  result*=h/3;
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
  cout << "Value of integral is: " << simpson13(n, lower, upper);
}
