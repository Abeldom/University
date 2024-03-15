#include <string.h>

#include <iostream>

using namespace std;

class E {
 protected:
  int e;

 public:
  E(char* szoveg, int x = 0) {
    e = x;
    strcat(szoveg, "E");
  }
};

class F {
 protected:
  int f;

 public:
  F(char* szoveg, int x = 0) {
    f = x;
    strcat(szoveg, "F");
  }
};

class A : public virtual E, public virtual F {
 protected:
  int a;

 public:
  A(char* szoveg, int x = 0) : E(szoveg, x), F(szoveg, x) {
    a = x;
    strcat(szoveg, "A");
  }
};

class B : public virtual E, public virtual F {
 protected:
  int b;

 public:
  B(char* szoveg, int x = 0) : E(szoveg, x), F(szoveg, x) {
    b = x;
    strcat(szoveg, "B");
  }
};

class C : public virtual E, public virtual F {
 protected:
  int c;

 public:
  C(char* szoveg, int x = 0) : E(szoveg, x), F(szoveg, x) {
    c = x;
    strcat(szoveg, "C");
  };
};

class D : public virtual E, public virtual F {
 protected:
  int d;

 public:
  D(char* szoveg, int x = 0) : E(szoveg, x), F(szoveg, x) {
    d = x;
    strcat(szoveg, "D");
  };
};

class G : public E, public F {
 protected:
  int g;

 public:
  G(char* szoveg, int x = 0) : E(szoveg, x), F(szoveg, x) {
    g = x;
    strcat(szoveg, "G");
  };
};

class H : public E, public F {
 protected:
  int h;

 public:
  H(char* szoveg, int x = 0) : E(szoveg, e), F(szoveg, f) {
    h = x;
    strcat(szoveg, "H");
  };
};

class I {
 protected:
  int i;

 public:
  I(char* szoveg, int x = 0) {
    i = x;
    strcat(szoveg, "I");
  };
};

class J : public virtual I,
          public A,
          public B,
          public C,
          public D,
          public G,
          public H {
 protected:
  int j;

 public:
  J(char* szoveg, int x = 0)
      : I(szoveg, x),
        A::E(szoveg, x),
        A::F(szoveg, x),
        A(szoveg, x),
        B(szoveg, x),
        C(szoveg, x),
        D(szoveg, x),
        G(szoveg, x),
        H(szoveg, x) {
    j = x;
    strcat(szoveg, "J");
  }
  void kiir() {
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;
    cout << "d=" << d << endl;
    cout << "e=" << A::e << endl;
    cout << "f=" << A::f << endl;
    cout << "g=" << g << endl;
    cout << "h=" << h << endl;
    cout << "i=" << i << endl;
    cout << "j=" << j << endl;
  }
};