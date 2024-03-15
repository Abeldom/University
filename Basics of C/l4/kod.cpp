#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream in("network.txt");
  int kiind, cel;
  int tomb[100][100];
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      tomb[i][j] = 0;
    }
  }

  int tav;
  while (in >> kiind) {
    in >> cel;

    in >> tav;
    tomb[kiind][cel] = 1;
    tomb[cel][kiind] = 1;
  }

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      cout << tomb[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}