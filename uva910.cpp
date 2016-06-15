#include <cstdio>
#include <cstring>

int dp[30][35];
int E[30][2];
int isEndPt[30];

int dfs(int position, int v) {
  if(v == 0) return isEndPt[position];

  if(dp[position][v] != -1) return dp[position][v];

  return (dp[position][v] = dfs(E[position][0], v - 1) + dfs(E[position][1], v - 1));
}

int ctoi(char c) {
  return c - 'A';
}

int main() {
  int n, m;
  char a, b, c, d;

  // freopen("input.txt", "r", stdin);

  while(scanf("%d\n", &n) != EOF) {
    memset(dp, -1, sizeof(dp));
    memset(E, 0, sizeof(E));
    memset(isEndPt, 0, sizeof(isEndPt));

    for(int i = 0; i < n; ++i) {
      scanf("%c %c %c %c\n", &a, &b, &c, &d);
      E[ctoi(a)][0] = ctoi(b);
      E[ctoi(a)][1] = ctoi(c);
      isEndPt[ctoi(a)] = (d == 'x')?1:0 ;
    }

    scanf("%d\n", &m);
    printf("%d\n", dfs(0, m));
  }

  return 0;
}
