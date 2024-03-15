#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

class Nev {
  char* keresztnev;
  char* csaladnev;

 public:
  Nev();
  Nev(const char*, const char*);
  Nev(const Nev&);
  ~Nev();
  char* get_keresztnev() const {return keresztnev};
  char* get_csaladnev() const { return csaladnev; }
  void kiir();
};

class Szemely {
 protected:
  Nev neve;
  int eletkor;

 public:
  Szemely();
  Szemely(Nev, int);
  Szemely operator++(int);
  Szemely& operator++();
  ostream& print(ostream&) const;

  void kiir();
};

class Diak : public Szemely {
  float atlag;

 public:
  Diak();
  Diak(Nev, int, float);
  void kiir();
};

#endif