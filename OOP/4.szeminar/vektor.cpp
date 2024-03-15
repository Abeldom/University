#include <iostream>
using namespace std;
#include "vektor.h"

vektor::vektor(int* v, int n) {
  cout << "inicializalo konstruktor" << endl;
  dim = n;
  elemek = new int[dim];
  for (int i = 0; i < dim; i++) {
    elemek[i] = v[i];
  }
}

void vektor::duplaz() {
  for (int i = 0; i < dim; i++) {
    elemek[i] *= 2;
  }
}

void vektor::kiir() {
  for (int i = 0; i < dim; i++) {
    cout << elemek[i] << " ";
  }
  cout << endl;
}

vektor::~vektor() {
  cout << "Destruktor" << endl;
  dim = 0;
  delete[] vektor;
}