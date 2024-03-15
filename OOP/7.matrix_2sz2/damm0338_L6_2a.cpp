//  Domokos Ábel
//  411

#include "damm0338_L6_2a.h"

int main() {
  Matrix m(1, 1, 1, 1);
  m.kiir();
  cout << "determinans erteke: " << ~m << endl;

  Matrix n;
  m += n;
  m.kiir();
  m *= n + m;
  m.kiir();

  return 0;
}