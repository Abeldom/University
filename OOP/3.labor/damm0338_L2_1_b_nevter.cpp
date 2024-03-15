#include <iostream>

#include "damm0338_L2_1_b_nevter.h"
using namespace std;

namespace intervallum {
double* intervallum;
void init(double, double);
void felsz();
void duplaz();
void kiir();
}  // namespace intervallum

void intervallum::init(double a, double b) {
  intervallum = new double[2];
  if (a > b) {
    double k = a;
    a = b;
    b = k;
  }
  intervallum[0] = a;
  intervallum[1] = b;
}

void intervallum::felsz() { delete[] intervallum; }

void intervallum::duplaz() {
  double k = (intervallum[1] - intervallum[0]) / 2;
  intervallum[0] -= k;
  intervallum[1] += k;
}

void intervallum::kiir() {
  cout << "(" << intervallum[0] << ", " << intervallum[1] << ")" << endl;
}