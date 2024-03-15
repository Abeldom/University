#include <iostream>
using namespace std;

static double* intervallum;

void init(double a, double b) {
  intervallum = new double[2];
  if (a > b) {
    double k = a;
    a = b;
    b = k;
  }
  intervallum[0] = a;
  intervallum[1] = b;
}

void felsz() { delete[] intervallum; }

void duplaz() {
  double k = (intervallum[1] - intervallum[0]) / 2;
  intervallum[0] -= k;
  intervallum[1] += k;
}

void kiir() {
  cout << "(" << intervallum[0] << ", " << intervallum[1] << ")" << endl;
}