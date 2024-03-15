#include <iostream>

using namespace std;

double negyzet(double x) { return x * x; }

void vegrehajt(double x, double (*p)(double)) { cout << (p)(x) << endl; }

int main() {
  double (*p)(double) = negyzet;
  cout << (p)(10);
  vegrehajt(10, p);

  return 0;
}