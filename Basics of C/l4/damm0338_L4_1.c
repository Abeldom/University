// Domokos Ábel
// 411 csoport
// 338 azonositoszam

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void kiir(int** matrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  srand(time(0));
  FILE* in = fopen("input.txt", "r");
  FILE* net = fopen("network.txt", "r");
  FILE* out = fopen("output.txt", "w");

  int pisti, julcsa;
  int kiindul, cel, tavolsag;
  int n = 0;
  int szaml = 0;
  int** matrix;

  matrix = (int**)malloc(0);

  while (fscanf(net, "%d %d %d  ", &kiindul, &cel, &tavolsag) != EOF) {
    if (kiindul + 1 > n || cel + 1 > n) {
      int prev_n = n;

      if (kiindul + 1 > n) n = kiindul + 1;
      if (cel + 1 > n) n = cel + 1;

      // letrehozom az uj sorokat
      matrix = (int**)realloc(matrix, n * sizeof(int*));

      // matrix oszlopbovitese
      for (int i = 0; i < prev_n; i++) {
        matrix[i] = (int*)realloc(matrix[i], n * sizeof(int));
        for (int j = prev_n; j < n; j++) {
          matrix[i][j] = 0;
        }
      }

      // matrix sorbovitese
      for (int i = prev_n; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
      }
    }

    matrix[cel][kiindul] = tavolsag;
    matrix[kiindul][cel] = tavolsag;
  }

  fscanf(in, "%d %d", &pisti, &julcsa);

  int from, to, dist = 0, found = 0;
  int daydist;
  for (int i = 0; i < 365; i++) {
    from = kiindul;
    daydist = 0;
    for (int j = 0; j < 2 * n && from != julcsa; j++) {
      do {
        to = rand() % n;
      } while (matrix[from][to] == 0);
      daydist += matrix[from][to];
      from = to;
    }
    if (from == julcsa) {
      found++;
      // printf("%d found\n", daydist);

    } else {
      // printf("%d not found\n", daydist);
    }
    dist += daydist;
  }
  fprintf(out, "%.2f \n%.2f", found / 3.65, dist / 365.00);

  for (int i = 0; i < n; i++) {
    free(matrix[i]);
  }
  free(matrix);
  fclose(in);
  fclose(net);
  fclose(out);
  return 0;
}