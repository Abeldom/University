#include <iostream>
#include <time.h>

using namespace std;

int veletlenSzam(int a, int b) { return rand() % (b - a + 1) + a; }

void jatek(int generaltSzam) {
  int tipp;
  cout << "tippem: ";
  cin >> tipp;
  while (tipp != generaltSzam) {
    if (tipp < generaltSzam) {
      cout << "nagyobbat\n";
    } else {
      cout << "kisebbet\n";
    }
    cout << "tippem: ";
    cin >> tipp;
  }
  cout << "Gratulalok!";
}

int main() {
  srand(time(NULL));
  int a, b;
  cin >> a >> b;
  int szam = veletlenSzam(a, b);
  cout << szam << endl;
  jatek(szam);

  return 0;
}