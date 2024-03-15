// Domokos Ábel
//  411
#include "main.h"

#include <iostream>

using namespace std;

int main() {
  try {
    GrayscalePoint val;
    val.kiir();
    cout << endl;
    GrayscalePoint szin(24);
    szin.kiir();
    cout << endl;

    szin += 35;
    szin.kiir();
    cout << endl;

    szin -= 60;
    szin.kiir();
    cout << endl;
  } catch (const char* hibauzenet) {
    cout << hibauzenet << endl;
  }
  cout << endl;
  try {
    GrayscalePoint r(14);
    GrayscalePoint g(250);
    GrayscalePoint b(224);

    ColorPoint szin(r, g, b);
    szin.kiir();
    cout << endl;

    szin++.kiir();
    szin.kiir();
    cout << endl;

    (++szin).kiir();
    szin.kiir();
    cout << endl;

    (szin += 3).kiir();
    cout << endl;

    (szin.getAsGray()).kiir();
    cout << endl << endl;

    (szin += 3).kiir();
    cout << endl;
  } catch (const char* hibauzenet) {
    cout << hibauzenet << endl;
  }
  return 0;
}