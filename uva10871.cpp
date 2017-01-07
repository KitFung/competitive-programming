#include <cstdio>
#include <cmath>
#include <cstring>

const int MAXN = 10010;

bool u[MAXN];
int su[MAXN];
int s[MAXN];

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

bool pri(int n) {
  if(n < 10010) return u[n];
  for(int i = 1; i < num; ++i)
    if(n % su[i] ==0)
      return false;
  return true;
}

int main() {
  int n = 10010;
  sieve_prime(n);

  int ncase;
  scanf("%d", &ncase);
  s[0] = 0;

  while(ncase--) {
    int tnum;
    scanf("%d", &tnum);
    for(int i = 1; i <= tnum; ++i) scanf("%d", &s[i]);

    for(int i = 1; i <= tnum; ++i) s[i] += s[i-1];

    bool ok = false;
    for(int d = 2; d <= tnum; ++d) {
      for(int i = 1; i <= tnum - d + 1; ++i) {
        int v = s[i+d-1] - s[i-1];
        if(pri(v)) {
          printf("Shortest primed subsequence is length %d:", d);
          for(int a = 1; a <= d; ++a) printf(" %d", s[i+a-1]-s[i+a-2]);
          printf("\n");
          ok = true;
          break;
        }
      }
      if(ok) break;
    }

    if(!ok) {
      printf("This sequence is anti-primed.\n");
    }
  }
  return 0;
}
