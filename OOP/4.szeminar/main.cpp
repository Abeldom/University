#include <iostream>
using namespace std;

// #include "vektor.cpp"
// #include "vektor.h"

class vektor {
  int* elemek;
  int dim;

 public:
  vektor();           // konstruktor
  vektor(int*, int);  // inicializáló
  // vektor(const vektor& v);// masolo
  ~vektor();  // destruktor
  void duplaz();
  void kiir();
  vektor osszead(const vektor& v);
};

vektor::vektor(int* v, int n) {
  cout << "inicializalo konstruktor" << endl;
  dim = n;
  elemek = new int[dim];
  for (int i = 0; i < dim; i++) {
    elemek[i] = v[i];
  }
}

vektor::vektor() {
  cout << "alapertelmezett konstruktor" << endl;
  elemek = new int[5];
  dim = 5;
  for (int i = 0; i < 5; i++) {
    elemek[i] = 0;
  }
}

vektor::vektor(const vektor& v) {  // cim szerint hogy ne keszitsen masolatot
  cout << "masolo konstruktor" << endl;
  dim = v.dim;
  elemek = new int[dim];
  for (int i = 0; i < dim; i++) {
    elemek[i] = v.elemek[i];
  }
}

void vektor::duplaz() {
  for (int i = 0; i < dim; i++) {
    elemek[i] *= 2;
  }
}

vektor vektor::osszead(const vektor& v) {
  if (dim != v.dim) {
    cout << "kulonbozo dimenziok. Nem vegezhetjuk el az osszeadast";
    vektor eredmeny;
    return eredmeny;
  } else {
    vektor v2(v);
    for (int i = 0; i < dim; i++) {
      v2.elemek[i] += v.elemek[i];
    }
    return v2;
  }
}

void vektor::kiir() {
  for (int i = 0; i < dim; i++) {
    cout << elemek[i] << " ";
  }
  cout << endl;
}

vektor::~vektor() {
  cout << "Destruktor" << endl;
  dim = 0;
  delete[] elemek;
}

int main() {
  // ha nem hozunk letre konstruktor a rendszer letrehoz egy alapertelmezett
  // konstruktort
  int elemek[] = {1, 2, 3, 4, 5};
  int db = 5;
  vektor v(elemek, db);  // inicializalo
  v.kiir();
  v.duplaz();
  v.kiir();

  vektor v2;  // alapertelmezett
  v2.kiir();
  v2.duplaz();
  v2.kiir();

  vektor v3(v);  // masolo konstruktor
  v3.kiir();
  v3.duplaz();
  v3.kiir();

  // vektor v4;
  // v4 = v.osszead(v2);

  return 0;
}