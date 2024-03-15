// Domokos Abel
// 338

#include <iostream>
using namespace std;

#include "damm0338_L2_1_a.h"
#include "damm0338_L2_1_b_nevter.h"
#include "damm0338_L2_1_b_osztaly.h"

int main() {
  int a, b;
  cout << "a=";
  cin >> a;
  cout << "b=";
  cin >> b;

  cout << "\n a) \n";
  init(a, b);
  kiir();
  duplaz();
  kiir();
  felsz();

  cout << "\n b) nevterek \n";
  intervallum::init(a, b);
  intervallum::kiir();
  intervallum::duplaz();
  intervallum::kiir();
  intervallum::felsz();

  cout << "\n b)osztalyok \n";
  Intervallum i(a, b);
  i.kiir();
  i.duplaz();
  i.kiir();
  // i.intervallum=0;
  return 0;
}