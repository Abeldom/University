#include "main.h"

#include <iostream>
using namespace std;

int main() {
  Nev ember;
  ember.kiir();
  cout << endl;

  try {
    Szemely karcsi(ember, +11);
    (++karcsi).kiir();
    cout << endl;
    karcsi.kiir();
    cout << endl;
    Diak judas(ember, 12, 4);
    judas.kiir();
  } catch (const char* uzenet) {
    cout << uzenet;
  }

  try {
  } catch (const char* uzenet) {
    cout << uzenet;
  }

  return 0;
}