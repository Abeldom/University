/*
tomb:
-maximum 100 eleme
-egesz ertekek
+inicializal
+ketszerez
+kiir
*/
#include <iostream>
using namespace std;

void inicializal(int* t, int h);
void ketszerez();
void kiir();

int main() {
  int finomsag[] = {1, 48, 2, 500};
  inicializal(finomsag, 4);
  ketszerez();
  kiir();
  return 0;
}
