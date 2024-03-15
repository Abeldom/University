#include <iostream>
using namespace std;

static int tomb[100];  // nem elerheto a masik allomanybol,
static int hossz;      // csak muveleteket tudunk vegezni

void inicializal(int *t, int h) {
  h = hossz;
  t = new int[h];
  for (int i = 0; i < h; i++) {
    tomb[i] = t[i];
  }
}

void ketszerez() {
  for (int i = 0; i < hossz; i++) {
    tomb[i] *= 2;
  }
}

void kiir() {
  for (int i = 0; i < hossz; i++) {
    cout << tomb[i] << " ";
  }
  cout << endl;
}
