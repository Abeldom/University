// osztaly nev: -csaladnev,keresztnev

// bitenkenti masolas, pointerek kivetel

#include <string.h>

#include <iostream>
using namespace std;

class Nev {
  char* cs_nev;
  char* k_nev;

 public:
  Nev();                          // alapert. konstr.
  Nev(const char*, const char*);  // ertekado inicializalo konstr.
  Nev(const Nev&);                // masolo konstr.
  ~Nev();

  char* get_cs_nev() const { return cs_nev; };
  char* get_k_nev() const { return k_nev; };

  void kiir();
};

class Szemely {
  int eletkor;
  Nev n;

 public:
  Szemely();
  Szemely(const Nev& valaki, int e);
  Szemely operator++(int);  // post++
  Szemely& operator++();    //++pre
  ostream& print(ostream& o) const;
};

class Diak : public Szemely {
  float atlag;

 public:
  Diak();
  Diak(const Nev& _n, int e, float atlag);
};

Diak::Diak() : Szemely() {
  cout << "Diak::alapertelmezett konstr." << endl;
  atlag = 10;
}

Diak::Diak(const Nev& _n, int e, float atlag) : Szemely(_n, e) {
  cout << "Diak::ertekado konstr." << endl;
  this->atlag = atlag;
}

Nev::Nev() {
  cout << "Nec::alapertelmezett konstruktor" << endl;
  cs_nev = new char[11];
  strcpy(cs_nev, "Ismeretlen");

  k_nev = new char[8];
  strcpy(k_nev, "Szemely");
}

Nev::Nev(const char* csnev, const char* knev) {
  cout << "Nev::inicializalo konstrutor." << endl;
  // cs_nev=csnev; //nnana, ezt nem igy.
  cs_nev = new char[strlen(csnev) + 1];
  strcpy(cs_nev, csnev);
  k_nev = new char[strlen(knev) + 1];
  strcpy(k_nev, knev);
}

Nev::Nev(const Nev& n) {
  cout << "Nev::masolo konstruktora" << endl;

  cs_nev = new char[strlen(n.cs_nev) + 1];
  cs_nev = n.cs_nev;

  k_nev = new char[strlen(n.k_nev) + 1];
  k_nev = n.k_nev;
}

Nev::~Nev() {
  cout << "Nev::destruktor" << endl;
  delete[] cs_nev;
  delete[] k_nev;
}

void Nev::kiir() { cout << cs_nev << " " << k_nev << endl; }

Szemely::Szemely() : n() {
  cout << "Szemelt::alapert. konstr." << endl;
  eletkor = 20;
}

Szemely::Szemely(const Nev& valaki, int e) : n(valaki) {
  cout << "Szemely::masolo konstr." << endl;
  if (e < 0) throw "Negativ eletkor";
  eletkor = e;
}

Szemely& Szemely::operator++() {
  eletkor++;
  return *this;
}

Szemely Szemely::operator++(int) {
  eletkor++;
  return Szemely(n, eletkor - 1);
}

ostream& Szemely::print(ostream& o) const {
  o << n.get_cs_nev() << " " << n.get_k_nev() << " " << eletkor << endl;
}

ostream& operator<<(ostream& o, const Szemely& sz) { return sz.print(o); }

int main() {
  Nev emberke("Matyas", "Daniel");
  Nev masik(emberke);  // masolo konstr
  masik.kiir();

  cout << "=============================" << endl;

  Nev n3;
  Szemely diak(n3, 1);
  try {
    cout << diak;
    cout << ++diak;
    cout << diak++;
    cout << "=============================" << endl;

    Diak d1(n3, 4, 11);
  } catch (const char* hibauzenet) {
    cout << hibauzenet << endl;
  }

  return 0;
}