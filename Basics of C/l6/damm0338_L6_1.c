// Domokos Ábel
// 411 csoport
// 338 azonositoszam

#include <stdio.h>
#include <stdlib.h>
struct palya {
  int allapot;
  int jovobeli_allapot;
};

void beolvas_meretek(int*, int*, int*);
int ellenorzes(int, int, int);
void palyaletrehozas(struct palya***, int, int);
void beolvas_koordinatak(struct palya***);
void gameoflife(struct palya***, int, int, int);
void eletmukodes(struct palya***, int, int);
int szomszedokszama(struct palya**, int, int, int, int);
void palyafrissites(struct palya***, int, int);
void kiiratas(struct palya***, int, int);
void torles(struct palya***, int);

int main(int argc, const char* argv[]) {
  if (argc != 4) {
    return 0;
  }
  int sor = atoi(argv[1]), oszlop = atoi(argv[2]), iteraciok = atoi(argv[3]);
  if (!ellenorzes(sor, oszlop, iteraciok)) {
    printf("hiba");
    return 0;
  }

  struct palya** palya;
  palyaletrehozas(&palya, sor, oszlop);
  beolvas_koordinatak(&palya);
  kiiratas(&palya, sor, oszlop);

  gameoflife(&palya, sor, oszlop, iteraciok);
  torles(&palya, sor);

  return 0;
}

int ellenorzes(int sor, int oszlop, int iteraciok) {
  if (sor < 3 || oszlop < 3 || iteraciok < 0) return 0;
  return 1;
}

void palyaletrehozas(struct palya*** palya, int sor, int oszlop) {
  (*palya) = (struct palya**)malloc(sor * sizeof(struct palya*));
  for (int i = 0; i < sor; i++) {
    (*palya)[i] = (struct palya*)malloc(oszlop * sizeof(struct palya));
    for (int j = 0; j < oszlop; j++) {
      (*palya)[i][j].allapot = 0;
    }
  }
}

void beolvas_koordinatak(struct palya*** palya) {
  FILE* in = fopen("input.txt", "r");
  int sor, oszlop;
  int counter = 0;
  while (fscanf(in, "%d %d", &sor, &oszlop) != EOF) {
    (*palya)[sor][oszlop].allapot = 1;
  }
}

void gameoflife(struct palya*** palya, int sor, int oszlop, int iteraciok) {
  for (int it = 0; it < iteraciok; it++) {
    printf("%d\n", it + 1);
    eletmukodes(palya, sor, oszlop);
    palyafrissites(palya, sor, oszlop);
    kiiratas(palya, sor, oszlop);
  }
}

void eletmukodes(struct palya*** palya, int sor, int oszlop) {
  int db;
  for (int i = 0; i < sor; i++) {
    for (int j = 0; j < oszlop; j++) {
      db = szomszedokszama(*palya, sor, oszlop, i, j);

      // tovabb el
      if ((*palya)[i][j].allapot == 1 && (db == 1 + 2 || db == 1 + 3)) {
        (*palya)[i][j].jovobeli_allapot = 1;
      }
      // szuletik
      else if ((*palya)[i][j].allapot == 0 && db == 1 + 2) {
        (*palya)[i][j].jovobeli_allapot = 1;
      } else {
        // halott lesz
        (*palya)[i][j].jovobeli_allapot = 0;
      }
    }
  }
}

int szomszedokszama(struct palya** palya, int sor, int oszlop, int x, int y) {
  int counter = 0;
  int ujsor, ujoszlop;

  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      ujsor = (sor + x + i) % sor;
      ujoszlop = (oszlop + y + j) % oszlop;
      if (palya[ujsor][ujoszlop].allapot == 1) {
        counter++;
      }
    }
  }
  return counter;
}

void palyafrissites(struct palya*** palya, int sor, int oszlop) {
  for (int i = 0; i < sor; i++) {
    for (int j = 0; j < oszlop; j++) {
      (*palya)[i][j].allapot = (*palya)[i][j].jovobeli_allapot;
    }
  }
}

void kiiratas(struct palya*** palya, int sor, int oszlop) {
  for (int i = 0; i < sor; i++) {
    for (int j = 0; j < oszlop; j++) {
      if ((*palya)[i][j].allapot == 1) {
        // printf("1");
        printf("%c", 219);
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

void torles(struct palya*** palya, int sor) {
  for (int i = 0; i < sor; i++) {
    free((*palya)[i]);
  }
  free(*palya);
}
