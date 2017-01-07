#include <cstdio>
#include <cmath>
#include <cstring>

const int MAXN = 10000010;

bool u[MAXN];
int su[MAXN];

int num;

void sieve_prime(int n) {
  num = 1;
  memset(u, true, sizeof(u));
  for(int i = 2; i <= n; ++i) {
    if(u[i]) su[num++] = i;
    for(int j = 1; j < num; ++j) {
      if(i*su[j] > n) break;
      u[i*su[j]] = false;
      if(i % su[j] == 0) break;
    }
  }
}

int main() {
  int n;
  n = 10000000;
  sieve_prime(n);

  int tnum;
  while(scanf("%d", &tnum) != EOF) {
    if(tnum < 8) printf("Impossible.\n");
    else if(tnum == 8) printf("2 2 2 2\n");
    else {
      if(tnum % 2 == 0) {
        tnum -= 4;
        printf("2 2 ");
      } else {
        tnum -= 5;
        printf("2 3 ");
      }
      for(int i = 1; i <= num; ++i) {
        if(su[i]*2 > n) break;
        if(u[tnum - su[i]]) {
          printf("%d %d\n", su[i], tnum-su[i]);
          break;
        }
      }
    }
  }
  return 0;
}
