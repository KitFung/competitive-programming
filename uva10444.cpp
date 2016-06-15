#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;

LL fac(int k) {
  LL sum = 1;
  for(int i = 2; i <= k; ++i)
    sum *= i;
  return sum;
}

int ncr(int n, int r) {
  if(r == 0 || n == r) return 1;
  r = min(r, n-r);

  LL nf = fac(n);
  LL rf = fac(r);
  LL nrf = fac(n - r);
  return nf/(rf * nrf);
}

int main() {
  int counter = 1;
  int n, p;

  while(scanf("%d%d", &n, &p) && (n || p)) {
    if(n == 0) {
      printf("Case %d: %d\n", counter++, 0);
    } else {
        int moved = 0;
        int result = 0;
        for(int k = 0; ;++k) {
          int num = ncr(p-3+k, k);
          int cost = 1 << k; // 2 ^ k
          if(moved + num >= n) {
            result += cost*(n - moved);
            break;
          } else {
            moved += num;
            result += cost * num;
          }
        }
        printf("Case %d: %d\n", counter++, result);
    }
  }

  return 0;
}
