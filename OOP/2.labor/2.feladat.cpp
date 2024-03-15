#include <math.h>

#include <iostream>
using namespace std;

void kiir(int* spiral, int meret) {
  cout << endl;
  for (int i = 0; i < meret; i++) {
    for (int j = 0; j < meret; j++) {
      cout << spiral[i * meret + j] << " ";
    }
  }
}

void spiralSorrend(const int* matrix, int n, int* spiral) {
  int meret = sqrt(n);
  int allapot = 0;
  int szaml = 0;
  for (int i = 0; i <= meret / 2; i++) {
    for (int j = i; j <= meret - 1 - i; j++) {  // vizszintes jobbra
      // spiral[i * meret + j] = matrix[szaml++];
      spiral[szaml++] = matrix[i * meret + j];
    }
    for (int j = (i + 1); j <= meret - 1 - i; j++) {  // fuggoleges le
      // spiral[j * meret + (meret - 1 - i)] = matrix[szaml++];
      spiral[szaml++] = matrix[j * meret + (meret - 1 - i)];
    }
    for (int j = meret - 2 - i; j >= i; j--) {  // vizszintes balra
      // spiral[((meret - 1) - i) * meret + j] = matrix[szaml++];
      spiral[szaml++] = matrix[((meret - 1) - i) * meret + j];
    }
    for (int j = meret - 2 - i; j > i; j--) {  // fuggoleges fel
      // spiral[(j)*meret + i] = matrix[szaml++];
      spiral[szaml++] = matrix[(j)*meret + i];
    }
  }
}

int main() {
  int n;
  cout << "matrix merete = n*n \n n= ";
  cin >> n;
  int* matrix = new int[n * n];
  int* spiral = new int[n * n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i * n + j] = i * n + j + 1;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << matrix[i * n + j] << " ";
    }
    cout << endl;
  }
  spiralSorrend(matrix, n * n, spiral);
  kiir(spiral, n);

  delete[] matrix;
  delete[] spiral;

  return 0;
}