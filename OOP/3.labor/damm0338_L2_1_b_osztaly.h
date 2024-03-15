#ifndef OSZTALY_H_INCLUDED
#define OSZTALY_H_INCLUDED

class Intervallum {
  double* intervallum;

 public:
  Intervallum(double, double);  // konstruktor
  ~Intervallum();               // destruktor
  void duplaz();
  void kiir() const;
};

#endif
