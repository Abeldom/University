#include <iostream>

#include "main.h"

using namespace std;

//---------------------------------------------
//      GRASCALE               GRASCALE
//---------------------------------------------

GrayscalePoint::GrayscalePoint() : szin(0) {
  cout << "Gs: Alapertelmezett konstruktor" << endl;
}

GrayscalePoint::GrayscalePoint(int ertek) {
  cout << "Gs: Inicializalo konstruktor" << endl;
  if (ertek < 0 || ertek > 255) throw "Nem letezo szin.";
  szin = ertek;
}

GrayscalePoint& GrayscalePoint::operator+=(int mertek) {
  cout << "Gs: Vilagosit. ";
  if (szin + mertek > 255 || szin + mertek < 0)
    throw "Gs: Nem lehetseges vilagositas.";
  szin += mertek;
  return *this;
}

GrayscalePoint& GrayscalePoint::operator-=(int mertek) {
  cout << "Gs: Sotetit. ";
  if (szin - mertek > 255 || szin - mertek < 0)
    throw "Gs: Nem lehetseges sotetites.";
  szin -= mertek;
  return *this;
}

void GrayscalePoint::kiir() const { cout << "(" << szin << ")"; }

//---------------------------------------------
//      COLOR POINT               COLOR POINT
//---------------------------------------------

ColorPoint::ColorPoint() : R(0), G(0), B(0) {
  cout << "CP: Alapertelmezett konstruktor" << endl;
}

ColorPoint::ColorPoint(GrayscalePoint& r, GrayscalePoint& g, GrayscalePoint& b)
    : R(r), G(g), B(b) {
  cout << "CP: Inicializalo konstruktor." << endl;
}

ColorPoint& ColorPoint::operator+=(int mertek) {
  cout << "CP: Vilagosit." << endl;

  R += mertek;
  G += mertek;
  B += mertek;
  return *this;
}

ColorPoint ColorPoint::operator++(int k) {
  cout << "CP: egysegnyit vilagosit. post" << endl;

  ColorPoint ujpont(R, G, B);
  R += 1;
  G += 1;
  B += 1;
  return ujpont;
}

ColorPoint& ColorPoint::operator++() {
  cout << "CP: egysegnyit vilagosit. pre" << endl;

  R += 1;
  G += 1;
  B += 1;
  return *this;
}

GrayscalePoint ColorPoint::getAsGray() {
  return GrayscalePoint(0.299 * R.get_szin() + 0.587 * G.get_szin() +
                        0.114 * B.get_szin());
}

void ColorPoint::kiir() {
  cout << "(";
  R.kiir();
  cout << ",";
  G.kiir();
  cout << ",";
  B.kiir();
  cout << ")" << endl;
}
