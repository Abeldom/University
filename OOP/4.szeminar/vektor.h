#ifndef VEKTOR_H_INCLUDED
#define VEKTOR_H_INCLUDED

class vektor {
  int* elemek;
  int dim;

 public:
  vektor();           // konstruktor
  vektor(int*, int);  // inicializáló
  vektor(const vektor& v);
  ~vektor();  // destruktor
  void duplaz();
  void kiir();
};

#endif
