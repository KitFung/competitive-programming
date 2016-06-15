#include <cstdio>
#include <cstring>
#include <cmath>

typedef long long LL;

const int MAXN = 1000010;

LL dp[MAXN];
LL sumdp[MAXN];

void build_dp() {
  memset(dp, 0, sizeof(dp));
  int counter = 1;
  for(int i = 4; i < MAXN; ++i) {
    dp[i] = counter + dp[i-2];
    sumdp[i] = dp[i] + sumdp[i-1];
    counter++;
  }
}

int main() {
  int n, m;

  build_dp();

  scanf("%d", &n);
  for(;n-- > 0;) {
    scanf("%d", &m);
    printf("%lld\n", sumdp[m]);
  }
  return 0;
}
