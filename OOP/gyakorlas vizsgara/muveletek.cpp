#include <string.h>

#include <iostream>

#include "main.h"
using namespace std;

//----------------------------------------------
//   NEV          NEV             NEV
//----------------------------------------------

Nev::Nev() {
  csaladnev = new char[6];
  strcpy(csaladnev, "Senki");
  keresztnev = new char[4];
  strcpy(keresztnev, "Fia");
}

Nev::Nev(const char* x_csaladnev, const char* x_keresztnev) {
  csaladnev = new char[strlen(x_csaladnev) + 1];
  keresztnev = new char[strlen(x_keresztnev) + 1];
  strcpy(csaladnev, x_csaladnev);
  strcpy(keresztnev, x_keresztnev);
}

Nev::Nev(const Nev& nev) {
  csaladnev = new char(strlen(nev.csaladnev) + 1);
  keresztnev = new char(strlen(nev.keresztnev) + 1);
  strcpy(csaladnev, nev.csaladnev);
  strcpy(keresztnev, nev.keresztnev);
}

Nev::~Nev() {
  delete[] csaladnev;
  delete[] keresztnev;
}

void Nev::kiir() { cout << csaladnev << " " << keresztnev; }

//----------------------------------------------
//   SZEMELY          SZEMELY             SZEMELY
//----------------------------------------------

Szemely::Szemely() : neve(), eletkor(0) {}

Szemely::Szemely(Nev nev, int ev) : neve(nev) {
  if (ev < 0) throw "Rossz ev";
  eletkor = ev;
}

Szemely Szemely::operator++(int k) {
  Szemely masolat(*this);
  eletkor++;
  return masolat;
}

Szemely& Szemely::operator++() {
  eletkor++;
  return *this;
}

void Szemely::kiir() {
  neve.kiir();
  cout << " " << eletkor;
}

//----------------------------------------------
//   DIAK          DIAK             DIAK
//----------------------------------------------

Diak::Diak() { atlag = 0; }

Diak::Diak(Nev ujnev, int ujeletkor, float ujatlag)
    : Szemely(ujnev, ujeletkor), atlag(ujatlag) {}

ostream& Szemely::print(ostream& o) const {
  o << neve.get_csaladnev() << " " << neve.get_keresztnev();
}

void Diak::kiir() {
  Szemely::kiir();
  cout << " " << atlag;
}

ostream& operator<<(ostream& o, const Szemely& szemely) {
  return szemely.print(o);
}