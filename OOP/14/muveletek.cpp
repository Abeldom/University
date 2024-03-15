#include <iostream>

#include "main.h"

using namespace std;

//  KONSTRUKTOROK

NagyEgesz::NagyEgesz() {
  //   cout << itr++ << ".konstruktor1  " << endl;
  elojel = 0;
  n = 1;
  szamjegy = new int[1];
  szamjegy[0] = 0;
}

NagyEgesz::NagyEgesz(int elojel, int n, const int* szamjegyek) {
  //   cout << itr++ << ".konstruktor2  " << endl;
  this->elojel = elojel;
  this->n = n;
  szamjegy = new int[n];
  for (int i = 0; i < n; i++) {
    szamjegy[i] = szamjegyek[i];
  }
}

NagyEgesz::NagyEgesz(const NagyEgesz& masolando) {
  //   cout << itr++ << ".konstruktor3  " << endl;
  elojel = masolando.elojel;
  n = masolando.n;
  szamjegy = new int[masolando.n];
  for (int i = 0; i < n; i++) {
    szamjegy[i] = masolando.szamjegy[i];
  }
}

NagyEgesz::NagyEgesz(int szam) {
  //   cout << itr++ << ".konstruktor4  " << endl;
  if (szam < 0) {
    elojel = -1;
    szam *= -1;
  } else if (szam == 0)
    elojel = 0;
  else
    elojel = +1;

  n = 0;
  int masol = szam;
  do {
    masol /= 10;
    n++;

  } while (masol != 0);

  szamjegy = new int[n];
  for (int i = n - 1; i >= 0; i--) {
    szamjegy[i] = szam % 10;
    szam /= 10;
  }
}

NagyEgesz::NagyEgesz(long long int szam) {
  // cout << ".konstruktor5  " << endl;
  if (szam < 0) {
    elojel = -1;
    szam *= -1;
  } else if (szam == 0)
    elojel = 0;
  else
    elojel = +1;

  n = 0;
  long long int masol = szam;
  do {
    masol /= 10;
    n++;

  } while (masol != 0);

  szamjegy = new int[n];
  for (int i = n - 1; i >= 0; i--) {
    szamjegy[i] = szam % 10;
    szam /= 10;
  }
}

// DESTRUKTOR

NagyEgesz::~NagyEgesz() {
  //   cout << --itr << "destr  " << endl;
  delete[] szamjegy;
}

// MUVELETEK

// ++++++

NagyEgesz NagyEgesz::operator+(const NagyEgesz& x) const {
  NagyEgesz ujszam(*this);
  if (elojel == x.elojel) {
    ujszam.osszead(x);
  } else {
    ujszam.kivon(x);
  }
  return ujszam;
}

NagyEgesz NagyEgesz::operator++(int k)  // postfix++
{
  NagyEgesz masol(*this);
  NagyEgesz uj(masol + 1);
  *this = uj;
  //   n = uj.n;
  //   elojel = uj.elojel;
  //   szamjegy = uj.szamjegy;

  return masol;
}

NagyEgesz& NagyEgesz::operator++()  //++prefix
{
  *this = NagyEgesz(*this + 1);
  return *this;
}

NagyEgesz& NagyEgesz::operator+=(const NagyEgesz& x) {
  *this = *this + x;
  return *this;
}

// ------

NagyEgesz NagyEgesz::operator-(NagyEgesz x) const {
  NagyEgesz ujszam(*this);
  x.elojel *= -1;
  if (elojel == x.elojel) {
    ujszam.osszead(x);
  } else {
    ujszam.kivon(x);
  }
  return ujszam;
}

NagyEgesz NagyEgesz::operator--(int)  // postfix++
{
  NagyEgesz masol(*this);
  NagyEgesz uj(masol - 1);
  *this = uj;
  //   n = uj.n;
  //   elojel = uj.elojel;
  //   szamjegy = uj.szamjegy;

  return masol;
}

NagyEgesz& NagyEgesz::operator--()  //++prefix
{
  *this = *this - 1;
  return *this;
}

NagyEgesz& NagyEgesz::operator-=(const NagyEgesz& x) {
  *this = *this - x;
  return *this;
}

// ******

NagyEgesz NagyEgesz::operator*(const NagyEgesz& y) const {
  // nulla hataresete
  if (elojel == 0 || y.elojel == 0) {
    return 0;
  }
  // elojel meghatarozasa
  int uj_elojel;
  if (elojel != y.elojel)
    uj_elojel = -1;
  else
    uj_elojel = 1;

  // uj szamjegytomb letrehozasa
  int uj_hossz = n + y.n;
  int ujszamjegyek[uj_hossz] = {0};

  // szorzas
  int s, maradek;
  for (int i = 1; i <= n; i++) {
    maradek = 0;
    for (int j = 1; j <= y.n; j++) {
      int elozo_ertek = ujszamjegyek[uj_hossz - i - j + 1];
      s = elozo_ertek + szamjegy[n - i] * y.szamjegy[y.n - j] + maradek;
      ujszamjegyek[uj_hossz - i - j + 1] = s % 10;
      maradek = s / 10;
    }
    ujszamjegyek[uj_hossz - i - y.n] = maradek;
  }

  if (maradek != 0) {
    ujszamjegyek[0] = maradek;
  } else {
    // nullas levagasa
    uj_hossz--;
    for (int i = 0; i < uj_hossz; i++) {
      ujszamjegyek[i] = ujszamjegyek[i + 1];
    }
  }
  return NagyEgesz(uj_elojel, uj_hossz, ujszamjegyek);
}

// protected kiegeszitok

NagyEgesz NagyEgesz::osszead(NagyEgesz y) {
  // elokeszit,rendez a nagysag szerint
  // mert a nagyobbikba fogom lementeni
  if (n < y.n) {
    swap(n, y.n);
    swap(szamjegy, y.szamjegy);
  }

  int maradek = 0;
  int s;

  // klasszikus osszeadas
  for (int i = 1; i <= y.n; i++) {
    s = szamjegy[n - i] + y.szamjegy[y.n - i] + maradek;
    szamjegy[n - i] = s % 10;
    maradek = s / 10;
  }
  // cout << szamjegy[0] << endl;

  // maradek hozzaadasa
  for (int i = n - y.n - 1; i >= 0; i--) {
    s = szamjegy[i] + maradek;
    szamjegy[i] = s % 10;
    maradek = s / 10;
  }

  if (maradek == 0) {
    return *this;
  }
  // bovites meg eggyel ha kell
  int ujszam[n + 1];
  ujszam[0] = 1;
  for (int i = 1; i <= n; i++) {
    ujszam[i] = szamjegy[i - 1];
  }

  return *this = NagyEgesz(elojel, n + 1, ujszam);
}

NagyEgesz NagyEgesz::kivon(NagyEgesz y) {
  // elokeszites, rendezes, mert az elsobe fogom lementeni az erteket;
  int eredmeny = nagyobb(*this, y);
  if (eredmeny == -1) {
    swap(n, y.n);
    swap(elojel, y.elojel);
    swap(szamjegy, y.szamjegy);
  } else if (eredmeny == 0) {
    return *this = 0;
  }

  int maradek = 0;
  int s;

  // klasszikus kivonas
  for (int i = 1; i <= y.n; i++) {
    s = 10 + szamjegy[n - i] - y.szamjegy[y.n - i] + maradek;
    szamjegy[n - i] = (s) % 10;
    if (s < 10) {
      maradek = -1;
    } else {
      maradek = 0;
    }
  }

  // a hosszabb szambol a levonandot meg levonjuk pl 100-1;
  for (int i = n - y.n - 1; i >= 0 && maradek != 0; i--) {
    s = 10 + szamjegy[i] + maradek;
    szamjegy[i] = (s) % 10;
    if (s < 10) {
      maradek = -1;
    } else {
      maradek = 0;
    }
  }

  // a szam elejen levo nullasok megszamlalasa
  int szaml = 0;
  while (szamjegy[szaml] == 0 && szaml < n) {
    szaml++;
  }
  if (szaml == 0) return *this;

  // atmasolni a megfelelo szamsort
  n = n - szaml;
  int ujtomb[n];
  for (int i = 0; i < n; i++) {
    ujtomb[i] = szamjegy[i + szaml];
  }

  // ujra lefoglalni a memoriat es lementeni veglegesen
  szamjegy = (int*)realloc(szamjegy, n * sizeof(int));
  for (int i = 0; i < n; i++) {
    szamjegy[i] = ujtomb[i];
  }
  return *this;
}

int NagyEgesz::nagyobb(NagyEgesz& x, NagyEgesz& y) {
  if (x.n > y.n)
    return 1;
  else if (x.n < y.n)
    return -1;

  for (int i = 0; i < x.n; i++) {
    if (x.szamjegy[i] > y.szamjegy[i])
      return 1;
    else if (x.szamjegy[i] < y.szamjegy[i])
      return -1;
  }
  return 0;
}

// <<<<<< kiiratas

void NagyEgesz::kiir() {
  if (elojel < 0) cout << "-";
  // else if (elojel > 0)
  // cout << "+";
  for (int i = 0; i < n; i++) {
    cout << szamjegy[i];
  }
}

ostream& NagyEgesz::print(ostream& o) const {
  if (elojel == -1) o << "-";
  // else
  // o << "+";

  // o << szamjegy[0];
  for (int i = 0; i < n; i++) {
    o << szamjegy[i];
  }
  return o;
}

ostream& operator<<(ostream& o, const NagyEgesz& sz) { return sz.print(o); }

// ======

NagyEgesz NagyEgesz::operator=(const NagyEgesz& y) {
  n = y.n;
  elojel = y.elojel;

  delete szamjegy;
  szamjegy = new int[n];
  for (int i = 0; i < n; i++) {
    szamjegy[i] = y.szamjegy[i];
  }

  return *this;
}
