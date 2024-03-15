#include <math.h>

#include <iostream>

template <typename T, int N>
class Matrix {
  T **A;

 public:
  Matrix();
  Matrix(T[]);
  Matrix(T[][N]);
  ~Matrix();
  void kiir() const;
  T **osszead(T[N][N]);

  double operator~();
};

template <typename T, int N>
double Matrix<T, N>::operator~() {
  double s = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      s += A[i][j] * A[i][j];
    }
  }
  return sqrt(s);
}

template <typename T, int N>
Matrix<T, N>::Matrix() {
  std::cout << "Konstruktor:\n";
  A = new T *[N];
  for (int i = 0; i < N; i++) {
    A[i] = new T[N];
    for (int j = 0; j < N; j++) {
      A[i][j] = (i == j) ? 1 : 0;
    }
  }
}

template <typename T, int N>
Matrix<T, N>::Matrix(T t[N][N]) {
  std::cout << "Konstruktor:\n";
  A = new T *[N];
  for (int i = 0; i < N; i++) {
    A[i] = new T[N];
    for (int j = 0; j < N; j++) {
      A[i][j] = t[i][j];
    }
  }
}

template <typename T, int N>
Matrix<T, N>::Matrix(T t[]) {
  std::cout << "Konstruktor:\n";
  A = new T *[N];
  for (int i = 0; i < N; i++) {
    A[i] = new T[N];
  }

  int i;
  for (i = 0; i < N * N; i++) {
    A[i / N][i % N] = t[i];
  }
}

template <typename T, int N>
Matrix<T, N>::~Matrix() {
  for (int i = 0; i < N; i++) {
    delete A[i];
  }
  std::cout << "Destruktor\n";
  delete A;
}

template <typename T, int N>
void Matrix<T, N>::kiir() const {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << A[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template <typename T, int N>
T **Matrix<T, N>::osszead(T a[N][N]) {
  T **ujmatrix = new T *[N];
  for (int i = 0; i < N; i++) {
    ujmatrix[i] = new T[N];
    for (int j = 0; j < N; j++) {
      ujmatrix[i][j] = A[i][j] + a[i][j];
    }
  }
  return ujmatrix;
}