#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
using namespace std;

class NagyEgesz {
  int n;
  int elojel;
  int* szamjegy;

 public:
  NagyEgesz();
  NagyEgesz(int elojel, int n, const int* szamjegyek);
  NagyEgesz(const NagyEgesz&);
  NagyEgesz(int szam);
  NagyEgesz(long long int szam);
  ~NagyEgesz();

  NagyEgesz operator+(const NagyEgesz&) const;
  NagyEgesz& operator++();    // ++pre
  NagyEgesz operator++(int);  // post++
  NagyEgesz& operator+=(const NagyEgesz&);

  NagyEgesz operator-(NagyEgesz) const;
  NagyEgesz& operator--();    // ++pre
  NagyEgesz operator--(int);  // post++
  NagyEgesz& operator-=(const NagyEgesz&);

  NagyEgesz operator*(const NagyEgesz&) const;
  NagyEgesz operator=(const NagyEgesz&);

  ostream& print(ostream& o) const;
  friend ostream& operator<<(ostream& o, const NagyEgesz&);

  void kiir();

 protected:
  int nagyobb(NagyEgesz&, NagyEgesz&);
  NagyEgesz kivon(NagyEgesz);
  NagyEgesz osszead(NagyEgesz);
};

#endif
