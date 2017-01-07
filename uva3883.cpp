#include <cstdio>
#include <cmath>
#include <cstring>

const int MAXN = 1300010;

bool u[MAXN];
int su[MAXN];
int res[MAXN];

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

  int pv = 0;
  int pidx = 1;
  for(int i = 1; i < num; ++i) {
    int v = su[i+1] - su[i];
    for(int from = su[i] + 1, to = su[i+1] - 1; from <= to; ++from)
      res[from] = v;
  }
}

int main() {
  int n = 1300000;
  sieve_prime(n);

  int tnum;
  while(scanf("%d", &tnum) != EOF && tnum) {
    if(u[tnum]) {
      printf("0\n");
      continue;
    }

    printf("%d\n", res[tnum]);
  }
  return 0;
}
