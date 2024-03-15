#include <iostream>
using namespace std;
#include "damm0338_L2_1_b_osztaly.h"

Intervallum::Intervallum(double a, double b) {
  intervallum = new double[2];
  if (a > b) {
    double k = a;
    a = b;
    b = k;
  }
  intervallum[0] = a;
  intervallum[1] = b;
}

Intervallum::~Intervallum() { delete[] intervallum; }

void Intervallum::duplaz() {
  double k = (intervallum[1] - intervallum[0]) / 2;
  intervallum[0] -= k;
  intervallum[1] += k;
}

void Intervallum::kiir() const {
  cout << "(" << intervallum[0] << ", " << intervallum[1] << ")" << endl;
}