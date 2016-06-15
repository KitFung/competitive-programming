#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int coins[5] = {1, 5, 10, 25, 50};

int dp[8000];


void run_dp() {
  memset(dp, 0, sizeof(dp));

  dp[0] = 1;
  for(int j = 0; j < 5; ++j) {
    for(int i = 0; i < 7500; ++i) {
        dp[i + coins[j]] += dp[i];
    }
  }
}

int main() {

  run_dp();

  int n;
  while(scanf("%d", &n) != EOF) {
    printf("%d\n", dp[n]);
  }

  return 0;
}
