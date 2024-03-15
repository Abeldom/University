// Domokos Ábel
// 411 csoport
// 338 azonositoszam

#include <stdbool.h>
#include <stdio.h>

bool joszam(int x) {
  if (x < 0 || x > 9) return false;
  return true;
}

int main() {
  char szoveg[256];

  FILE* in;
  in = fopen("input.txt", "r");
  FILE* out;
  out = fopen("output.txt", "w");

  char ch;
  int szoveghossz = 0;
  while ((ch = fgetc(in)) != EOF) {
    szoveg[szoveghossz] = ch;
    szoveghossz++;
  }

  fscanf(in, "%s", szoveg);

  // szamok beolvasasa
  int x, y, z;
  scanf("%d %d %d", &x, &y, &z);
  if (!(joszam(x) && joszam(y) && joszam(z))) {
    printf("nem jo szamokat adtal meg");
    return 0;
  }

  // szo beolvasasa
  char szo[3] = "";
  scanf("%s", szo);

  if (szo[3] != '\0') {
    fprintf(out, "%s", "rossz szot adtal meg");
    printf("%s", "rossz szot adtal meg");
    return 0;
  }

  // titkositasi folyamat
  int szo_bitterkep = szo[0] & szo[1] | szo[2];
  int D = (~x << (y + z));

  for (int i = 0; i < szoveghossz; i++) {
    int c = szoveg[i] ^ D ^ szo_bitterkep;
    fprintf(out, "%c", (char)c);
  }

  for (int j = 0; j != 25; j++) {
    int i = j;
    if ((i > 6 && i < 11) || i == 13) {
      if (i < 10)
        printf("|  %d [0x0%d]:   ", i, i);
      else
        printf("| %d [0x0%x]:   ", i, i);
      i += 26;
    }
    while (i < 256) {
      printf("|");

      if (i < 10)
        printf("  ", i);
      else if (i < 100)
        printf(" ", i);
      printf("%d ", i);

      if (i < 16)
        printf("[0x0%x]: ", i);
      else
        printf("[0x%x]: ", i);

      printf("%c ", i);
      i += 26;
    }
    printf("\n");
  }
  fclose(in);
  fclose(out);

  return 0;
}
