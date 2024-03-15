// Domokos Abel
//  411

#include "damm0338_L5_1_a.h"

int main() {
  int t[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      t[i][j] = i + j;
    }
  }

  std::cout << "Egysegmatrix:\n";
  Matrix<int, 3> m;
  m.kiir();

  std::cout << "Matrix szerinti inicializalas\n";
  Matrix<int, 3> masik(t);
  masik.kiir();

  std::cout << "Tomb szerinti inicializalas\n";
  int A[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix<int, 3> harmadik(A);
  harmadik.kiir();

  std::cout << "Matrixok osszeadasa:\n";
  int** kiirando = harmadik.osszead(t);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      std::cout << kiirando[i][j] << " ";
    }
    std::cout << std::endl;
  }
  for (int i = 0; i < 3; i++) {
    delete[] kiirando[i];
  }
  delete[] kiirando;

  double ertek = ~harmadik;
  std::cout << ertek;
  // ez valamiert nem mukodik, de a fuggvenyt megirtam ra

  return 0;
}