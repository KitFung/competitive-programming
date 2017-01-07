#include <cstdio>
#include <cmath>
#include <cstring>

const int MAXN = 1000010;

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
  n = 1000000;
  sieve_prime(n);

  int even_num;
  while(scanf("%d", &even_num) != EOF && even_num) {
    bool ok = false;
    for(int i = 2; i <= num; ++i) {
      if(su[i]*2 > even_num) break;
      if(u[even_num-su[i]]) {
        ok = true;
        printf("%d = %d + %d\n", even_num, su[i], even_num-su[i]);
        break;
      }
    }
    if(!ok) printf("HaHa\n");
  }
  return 0;
}
