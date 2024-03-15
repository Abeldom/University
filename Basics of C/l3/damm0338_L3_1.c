// Domokos Ábel
// 411 csoport
// 338 azonositoszam

#include <stdio.h>
#include <time.h>

#include "damm0338_mode.h"

#if mode == 1
#include "damm0338_normal.h"
#elif mode == 2
#include "damm0338_inline.h"
#else
#include "damm0338_macro.h"
#endif

int fib(int n) {
  if (n < 1)
    return 0;
  else if (n == 1)
    return 1;
  return add(fib(n - 1), fib(n - 2));
}

float fibsebesseg(int n) {
  clock_t start_t, end_t, total_t;

  start_t = clock();
  fib(n);
  end_t = clock();

  total_t = end_t - start_t;
  return (float)total_t / CLOCKS_PER_SEC;
}

int main() {
  FILE* in = fopen("input.txt", "r");
  FILE* out = fopen("output.txt", "a");

  int n;
  fscanf(in, "%d", &n);

  fprintf(out, "fibonacci(%d) = %d \n%s \n", n, fib(n), STR);
  float timesum = 0;
  for (int i = 0; i < 5; i++) {
    float thistime = fibsebesseg(n);

    timesum += thistime;
    fprintf(out, "#%d run: %f\n", i + 1, thistime);
  }

  fprintf(out, "average: %f \n\n", (float)timesum / 5);
  fclose(in);
  fclose(out);
  return 0;
}