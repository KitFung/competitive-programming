#include <cstdio>
#include <cstring>
#include <cmath>
const int MAXN = 20000001;
unsigned long long dp[MAXN];
unsigned long long fac[MAXN];

unsigned long long lvd() {

  int limit = sqrt(MAXN) + 1;


  for(int i = 1; i < MAXN; ++i) {
    for(int t = i * 2; t < MAXN; t += i)
      fac[t] += i;
  }

}

void dodp() {
  dp[0] = 0;
  dp[1] = 0;
  dp[2] = 3;
  for(int i = 3; i < MAXN; ++i) {
    unsigned long long thisv = i + fac[i];
    dp[i] = dp[i-1] + thisv;
  }
}

int main() {

  int n;
  lvd();
  dodp();
  while(scanf("%d", &n) != EOF && n) {
    printf("%lld\n", dp[n]);
  }
  return 0;
}
