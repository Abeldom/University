// Domokos Abel
// 411
#include <iostream>
using namespace std;

char* szotkeres(char* elemzett, char* keresendo) {
  int elsobetu = 0;

  while (elemzett[elsobetu] != '\0') {
    int szoban = elsobetu;

    while (elemzett[szoban] == keresendo[szoban - elsobetu]) {
      // cout << "d" << szoban << " ";
      szoban++;
      if (keresendo[szoban - elsobetu] == '\0') {
        return &elemzett[elsobetu];
      }

      if (elemzett[szoban] == '\0') throw "nem talalt";
    }
    // cout << "nem stimmel\n ";
    elsobetu++;
  }
  throw "nem talalt";
  return '\0';
}

int main() {
  char szo[] = "foepulet, op szeminarium, sajtos pizza";
  char szo2[] = "pizza";

  try {
    szotkeres(szo, szo2);
    cout << "talalt";
  } catch (const char* e) {
    cout << e << "\n";
  }

  return 0;
}