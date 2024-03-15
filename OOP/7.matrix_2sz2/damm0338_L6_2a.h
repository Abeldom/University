// Domokos Ábel
// 411

#include <iostream>
using namespace std;

class Matrix {
    double a11, a12, a21, a22;

public:
    Matrix();
    Matrix(double, double, double, double);

    double operator~();
    Matrix operator+(const Matrix);
    Matrix& operator+=(const Matrix);
    Matrix operator*(const Matrix);
    Matrix& operator*=(const Matrix);

    void kiir();
};

Matrix::Matrix()
{
    a11 = 1;
    a12 = 0;
    a21 = 0;
    a22 = 1;
}

Matrix::Matrix(double a1, double a2, double a3, double a4)
{
    a11 = a1;
    a12 = a2;
    a21 = a3;
    a22 = a4;
}

Matrix Matrix::operator+(const Matrix k)
{
    Matrix uj(a11 + k.a11, a12 + k.a12, a21 + k.a21, a22 + k.a22);
    return uj;
}

Matrix& Matrix::operator+=(const Matrix k) { return *this = *this + k; }

Matrix Matrix::operator*(const Matrix k)
{
    Matrix uj(a11 * k.a11 + a12 * k.a21, a11 * k.a12 + a12 * k.a22,
        a21 * k.a11 + a22 * k.a21, a21 * k.a12 + a22 * k.a22);
    return uj;
}

Matrix& Matrix::operator*=(const Matrix k) { return *this = *this * k; }

void Matrix::kiir()
{
    cout << a11 << " " << a12 << "\n"
         << a21 << " " << a22 << endl;
}

double Matrix::operator~() { return a11 * a22 - a12 * a21; }
