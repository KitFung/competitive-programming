#include <cstdio>
#include <cmath>
#include <cstring>

const int MAXN = 1000010;

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
}

bool isdigitprime(int n) {
  int v = 0;
  while(n > 0) {
    v += n %10;
    n /= 10;
  }
  return u[v];
}

int main() {
  int n;
  n = 1000000;
  sieve_prime(n);

  memset(res, 0, sizeof(res));
  for(int i = 2; i < MAXN; ++i) {
    res[i] += res[i-1];
    if(u[i] && isdigitprime(i)) ++res[i];
  }

  int ncase;
  scanf("%d", &ncase);
  int from, to;
  while(ncase--) {
    scanf("%d %d", &from, &to);
    printf("%d\n", res[to] - res[from-1]);
  }
  return 0;
}
