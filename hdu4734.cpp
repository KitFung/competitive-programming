#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>

int dp[10][2000];
int num[10];
int w;
int accum;

int ten[10];


int dodp(int len, int cw, int an, bool limitR) {
  if(len == 0) return cw <= w;
  if(cw > w) return 0;
  if(!limitR && dp[len][cw] != -1)
    return dp[len][cw];

  int limit = limitR?num[len]:9;
  int ans = 0;
  int next_an = an>>1;
  for(int i = 0; i <= limit; ++i) {
    int tmp = cw + i*an;
    if(tmp > w) continue;
    if(!limitR && tmp+9*(an-1)<= w) {
      // max weight when n = 1, 2, 3, 4, 5  = 9 ,27, 63, 135
      //                   = 9 * (2^0 + 2^1 + ... 2^n)
      //                   = 9 * (2^(n+1) - 1)
      ans += ten[len - 1];
    } else if (tmp == w) {
      ans++;
    } else {
      ans += dodp(len-1, tmp, next_an, limitR&&i==limit);
    }
  }

  if(!limitR) dp[len][cw] = ans;

  return ans;
}

void calc_weight(int n) {
  int ac = 1;
  w = 0;
  while(n > 0) {
    w += ac * (n % 10);
    n /= 10;
    ac <<= 1;
  }
}

int solve(int n) {
  int len = 1;
  accum = 1;
  while(n > 0) {
    num[len++] = n % 10;
    n /= 10;
    accum <<= 1;
  }
  accum >>= 1;
  len--;
  // printf("len: [%d]  accum: [%intd]  w: [%intd]\n", len, accum, w);
  return dodp(len, 0, accum, true);
}

int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  int T;
  int a, b;
  // clock_t begin_time = clock();
  ten[0] = 1;
  for(int i = 1; i < 10; ++i) ten[i] = ten[i-1]*10;
  scanf("%d", &T);
  for(int tc = 1; tc <= T; ++tc) {
    memset(dp, -1, sizeof(dp));
    scanf("%d%d", &a, &b);
    calc_weight(a);
    printf("Case #%d: %d\n", tc, solve(b));
  }
  // printf("%lf\n", float( clock () - begin_time ));
}
