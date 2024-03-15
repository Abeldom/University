// Domokos Ábel
//  411

#include "main.h"

#include <iostream>
using namespace std;

int main() {
  // konstruktorok
  NagyEgesz nulla;
  cout << "  nulla: ";
  nulla.kiir();
  cout << endl;

  int v[30] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
               9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
  NagyEgesz szam_vektor(1, 30, v);  //(negativ,42 szamjegy, szamjegyek tombje)
  cout << " vektor: ";
  szam_vektor.kiir();
  cout << endl;

  NagyEgesz masolat(szam_vektor);
  cout << "masolat: ";
  masolat.kiir();
  cout << endl;

  NagyEgesz szam_long(123456789012345678);
  cout << "   long: ";
  szam_long.kiir();
  cout << endl << endl;

  //++++++++
  NagyEgesz szam = szam_vektor;
  NagyEgesz szam2(szam_long);
  NagyEgesz sum = szam + szam2;

  cout << szam << " + " << szam2 << " = " << sum << endl;
  cout << "postfix++: " << sum++ << endl;
  cout << " ++prefix: " << ++sum << endl;
  cout << "    +=   : " << (sum += 5) << endl << endl;

  // ---------
  sum = szam - szam2;

  cout << szam << " - " << szam2 << " = " << sum << endl;
  cout << "postfix--: " << sum-- << endl;
  cout << " --prefix: " << --sum << endl;
  cout << "    -=   : " << (sum -= 5) << endl << endl;

  //*********
  NagyEgesz szorzat = szam * szam2;

  cout << szam << " * " << szam2 << " = " << szorzat << endl;

  return 0;
}
