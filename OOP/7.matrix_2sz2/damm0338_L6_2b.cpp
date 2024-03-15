// Domokos Ábel
// 411

#include "damm0338_L6_2b.h"

int main() {
  Intervallum inter;
  inter.kiir();

  try {
    Intervallum helytelen(11, 1);
  } catch (const char* s) {
    cout << s << endl;
  }

  Intervallum jojo(1, 4);
  jojo--.kiir();
  jojo.kiir();
  (--jojo).kiir();
  jojo.kiir();

  return 0;
}