#include <cstdio>
#include <cstring>

typedef long long LL;

// len | have 13 | preNum | mod
LL dp[15][2][10][13];
LL num[15];

LL dodp(int len, int preMod, int preNum, bool have13, bool limitR) {
  if(len == 0) return have13 && preMod == 0;
  int type = 0;

  if(!limitR && dp[len][have13][preNum][preMod] != -1)
    return dp[len][have13][preNum][preMod];

  int limit = limitR?num[len]:9;
  LL ans = 0;
  for(int i = 0; i <= limit; ++i) {
    ans += dodp(len-1, (((preMod*10)%13)+i)%13, i, have13||(preNum==1&&i==3), limitR&&i==limit);
  }
  if(!limitR) {
    dp[len][have13][preNum][preMod] = ans;
  }
  return ans;
}

int count_digit(LL n) {
  memset(num, 0, sizeof(num));
  int len = 1;
  while(n > 0) {
    num[len++] = n % 10;
    n /= 10;
  }
  return len - 1;
}


int main() {
  // freopen("input.txt", "r", stdin);
  memset(dp, -1, sizeof(dp));

  LL n;
  while(scanf("%lld", &n) != EOF) {
    int len = count_digit(n);
    printf("%lld\n", dodp(len, 0, 0, false, true));
  }
  return 0;
}
