// Domokos Ábel
// 411 csoport
// 338 azonositoszam

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool beolvasas(char szoveg[], int* kodhossz) {
  FILE* in;
  if ((in = fopen("input.txt", "r"))) {
    char ch;
    (*kodhossz) = 0;
    while ((ch = fgetc(in)) != EOF) {
      if (isdigit(ch)) {
        szoveg[*kodhossz] = ch;
        (*kodhossz)++;
      }
    }
    fclose(in);
    return 1;
  }
  return 0;
}

//--> ellenorzeshez tartozok
bool a_hossz(int kodhossz) {
  if (kodhossz > 11 && kodhossz < 20) return true;
  return false;
}

bool b_Luhn(char szoveg[], int kodhossz) {
  int utolso = szoveg[kodhossz - 1] - 48;
  kodhossz -= 2;
  int s = 0;
  for (int i = 0; i <= kodhossz; i++) {
    int szam = szoveg[kodhossz - i] - 48;
    if (i % 2 == 0) {
      szam *= 2;
      if (szam > 9) {
        szam -= 9;
      }
    }
    s += szam;
  }
  s += utolso;
  if (s % 10 != 0) {
    return false;
  }

  return true;
}
//<-- ellenorzeshez tartozok

bool ellenorzes(char szoveg[], int kodhossz) {
  if (!a_hossz(kodhossz)) return false;
  if (!b_Luhn(szoveg, kodhossz)) return false;

  return true;
}

//-->azonositashoz tartozok
int szovegetszamma(char szoveg[], int mennyit) {
  int elsonegy = 0;
  for (int i = 0; i < mennyit; i++) {
    int x = szoveg[i] - 48;
    elsonegy = elsonegy * 10 + x;
  }
  return elsonegy;
}

bool VISA(int szam, int kodhossz) {
  if ((kodhossz == 13 || kodhossz == 16) && ((szam / 1000) == 4)) {
    return true;
  }
  return false;
}

bool Maestro(int szam, int kodhossz) {
  if (szam == 5018 || szam == 5020 || szam == 5038 || szam == 5893 ||
      szam == 6304 || szam == 6759 || szam == 6761 || szam == 6762 ||
      szam == 6763)
    return true;
  return false;
}

bool Mastercard(int szam, int kodhossz) {
  if (kodhossz == 16) {
    if (szam / 100 < 56 && szam / 100 > 50) return true;
    if (szam > 2220 && szam < 2721) return true;
  }
  return false;
}

bool AmericanExpress(int szam, int kodhossz) {
  if (kodhossz == 15 && (szam / 100 == 37 || szam / 100 == 34)) {
    return true;
  }
  return false;
}

bool DinersClubInternational(int szam, int kodhossz) {
  return ((kodhossz > 13 && kodhossz < 20) && (szam / 100 == 36));
}

void tipusletrehozas(char tip[], char tipus[], int hossz) {
  for (int i = 0; i < hossz; i++) {
    tipus[i] = tip[i];
  }
  tipus[hossz] = '\0';
}
//<--azonositashoz tartozok

void azonositas(char szoveg[], char tipus[], int kodhossz) {
  int elsonegy = szovegetszamma(szoveg, 4);

  char* tip;
  int hossz = 0;

  if (VISA(elsonegy, kodhossz)) {
    tip = "VISA";
    hossz = 4;
  } else if (Mastercard(elsonegy, kodhossz)) {
    tip = "Mastercard";
    hossz = 10;
  } else if (AmericanExpress(elsonegy, kodhossz)) {
    tip = "AmericanExpress";
    hossz = 15;
  } else if (DinersClubInternational(elsonegy, kodhossz)) {
    tip = "DinersClubInternational";
    hossz = 23;
  } else if (Maestro(elsonegy, kodhossz)) {
    tip = "Maestro";
    hossz = 7;
  } else {
    tip = "egyeb";
    hossz = 5;
  }
  tipusletrehozas(tip, tipus, hossz);
}

void kiiratas(bool eredmeny, char* tipus, int kodhossz) {
  FILE* out = fopen("output.txt", "w");
  if (eredmeny) {
    fprintf(out, "%s", tipus);
  } else if (kodhossz == -1) {
    fprintf(out, "%s", "nincs bemeneti allomany");
  } else {
    fprintf(out, "ervenytelen");
  }
  fclose(out);
}

int main() {
  char szoveg[20];
  char tipus[23];
  int kodhossz = -1;
  int eredmeny;  // jo vagy milyen hibatipus

  if (!beolvasas(szoveg, &kodhossz)) {
    kiiratas(0, tipus, kodhossz);
    return 0;
  }

  if (!ellenorzes(szoveg, kodhossz)) {
    kiiratas(0, tipus, kodhossz);
    return 0;
  }

  azonositas(szoveg, tipus, kodhossz);
  kiiratas(eredmeny, tipus, kodhossz);

  return 0;
}
