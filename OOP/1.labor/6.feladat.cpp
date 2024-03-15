#include <iostream>
using namespace std;

static inline int minimum(int a, int b) { return (a < b) ? a : b; }
static inline int maximum(int a, int b) { return (a > b) ? a : b; }

int main() {
  int a = 2, b = 3;
  int kicsi = minimum(a, b);
  int nagy = maximum(a, b);

  return 0;
}