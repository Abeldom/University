// Domokos Ábel
// 411 csoport
// 338 azonositoszam

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void kiir_szoveg(char** v, int ettol, int eddig) {
  FILE* out = fopen("output.txt", "w");

  for (int i = ettol - 1; i < eddig - 1; i++) {
    fprintf(out, "%s \n", v[i]);
  }
  fprintf(out, "%s", v[eddig - 1]);

  fclose(out);
}

int atalakit(const char* szo) {
  int szam = 0;
  for (int i = 0; i < strlen(szo); i++) {
    if (isdigit(szo[i])) {
      int szamjegy = szo[i] - '0';
      szam = szam * 10 + szamjegy;
    } else {
      return -1;
    }
  }
  return szam;
}

int main(int argc, const char* argv[]) {
  FILE* in = fopen("input.txt", "r");
  FILE* out = fopen("output.txt", "w");

  if (argc != 3) {
    fprintf(out, "hiba");
    return 0;
  }

  int ettol = atalakit(argv[1]);
  int eddig = atalakit(argv[2]);
  if (ettol == -1 || eddig == -1 || ettol > eddig) {
    fprintf(out, "hiba");
    return 0;
  }

  char** szoveg = (char**)malloc(sizeof(char*));
  szoveg[0] = (char*)malloc(0);

  size_t sor = 0;
  size_t oszlop = 0;

  // beolvasas es szovegepites
  char ch;
  while (fscanf(in, "%c", &ch) != EOF) {
    if (ch == '\n') {
      oszlop = 0;
      sor++;
      szoveg = (char**)realloc(szoveg, (sor + 1) * sizeof(char*));
      szoveg[sor] = (char*)malloc(0);
    } else {
      oszlop++;
      szoveg[sor] = (char*)realloc(szoveg[sor], (oszlop + 1) * sizeof(char));
      szoveg[sor][oszlop - 1] = ch;
      szoveg[sor][oszlop] = '\0';
    }
  }
  sor++;
  if (sor < eddig) {
    fprintf(out, "hiba");
    return 0;
  }
  // segitotombok
  int betukdb[10] = {5, 3, 5, 5, 4, 2, 3, 3, 5, 6};
  const char* szamokbetuvel[10] = {"nulla", "egy", "ketto", "harom", "negy",
                                   "ot",    "hat", "het",   "nyolc", "kilenc"};

  // felmunkara
  for (int i = ettol - 1; i < eddig; i++) {
    for (int j = 0; j < strlen(szoveg[i]); j++) {
      //
      if (isdigit(szoveg[i][j])) {
        int szam = (int)szoveg[i][j] - 48;
        int ujhossz = strlen(szoveg[i]) + betukdb[szam] - 1;

        // sor bovitese
        szoveg[i] = (char*)realloc(szoveg[i], (ujhossz + 1) * sizeof(char));

        // szovegresz elhuzasa a sor vegebe
        memmove((szoveg[i] + j) + betukdb[szam], szoveg[i] + j + 1,
                strlen(szoveg[i] + j + 1) + 1);  //+1 a /0 miatt

        // szo atmasolasa
        memmove(szoveg[i] + j, szamokbetuvel[szam], betukdb[szam]);

        j += betukdb[szam] - 1;
      }
    }
  }
  // munkavege

  kiir_szoveg(szoveg, ettol, eddig);

  // >--felszabadit--<>--zar--<
  for (int i = 0; i < sor; i++) {
    free(szoveg[i]);
  }
  free(szoveg);
  fclose(in);
  fclose(out);

  return 0;
}
