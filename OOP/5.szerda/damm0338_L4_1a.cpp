// Domokos Abel
// 411

#include <iostream>
using namespace std;

class Lista {
  int n;
  int maxhossz;
  int* e;

 public:
  Lista(int);
  ~Lista();
  int pop();
  void push(int);
  class Betelt {};
  class Ures {};
};

Lista::Lista(int hossz) {
  maxhossz = hossz;
  n = 0;
  e = new int[maxhossz];
}

Lista::~Lista() { delete[] e; }

void Lista::push(int a) {
  if (n >= maxhossz) {
    throw Betelt();
  }
  e[n++] = a;
}

int Lista::pop() {
  if (n == 0) {
    throw Ures();
  }
  int elso = e[0];
  for (int i = 0; i < n - 1; i++) {
    e[i] = e[i + 1];
  }
  n--;
  return elso;
}

int main() {
  Lista lista(5);
  try {
    for (int i = 0; i < 6; i++) {
      lista.push(i);
      cout << i << " ";
    }
  } catch (Lista::Betelt) {
    cout << "Betelt a lista \n";
  }

  try {
    for (int i = 0; i < 7; i++) {
      cout << lista.pop() << " kiveve \n";
    }
  } catch (Lista::Ures) {
    cout << "Ures a lista \n";
  }

  return 0;
}