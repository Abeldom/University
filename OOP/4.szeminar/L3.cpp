// Domokos Abel
// 411

#include <math.h>
#include <time.h>

#include <iostream>
using namespace std;

class pont {
  float x, y;

 public:
  pont();              // nullara inicializal
  pont(float, float);  // special ertekekre inicializal
  float x_koord();
  float y_koord();
};

class kor {
  pont kozeppont;  // kor kozeppontja - O
  float sugar;     //

 public:
  kor();
  kor(pont, float);
  float terulet();
  float kerulet();
  pont randompont();
};

pont::pont() {
  x = 0;
  y = 0;
}

pont::pont(float a, float b) {
  x = a;
  y = b;
}

float pont::x_koord() { return x; }

float pont::y_koord() { return y; }

kor::kor() {
  pont ujpont;
  kozeppont = ujpont;
  sugar = 1;
};

kor::kor(pont P, float r) {
  kozeppont = P;
  sugar = r;
}

float kor::terulet() { return M_PI * sugar * sugar; }

float kor::kerulet() { return 2 * M_PI * sugar; }

pont kor::randompont() {
  float szog = (rand() % 3600) * 10;
  float x = cos(szog / 360 * M_PI);
  float y = sin(szog / 360 * M_PI);
  pont randompont(x + kozeppont.x_koord(), y + kozeppont.y_koord());

  cout << "randompont: x=" << x << "  y=" << y << endl;
  return randompont;
}

int main() {
  srand(time(NULL));
  pont a(0, 2);
  kor Kor(a, 5);

  cout << "kerulet= " << Kor.kerulet() << endl;
  cout << "terulet= " << Kor.terulet() << endl;
  cout << Kor.randompont().x_koord();
  return 0;
}