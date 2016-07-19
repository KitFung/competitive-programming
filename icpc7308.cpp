#include <cstdio>
#include <cmath>


int main() {
  int ncase, R, V;
  scanf("%d", &ncase);
  for(int i = 1; i<= ncase; ++i) {
    scanf("%d%d", &R, &V);
    printf("Case %d: %.8lf\n", i, (2.0*M_PI*R)/4.0/V);
  }
  return 0;
}
