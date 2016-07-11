#include <cstdio>
#include <cstring>

typedef long long LL;

LL num[15];

LL dodfs(int len, bool preSix, bool limitR) {
  if(len == 0) return 1;
  LL result = 0;
  int limit = limitR?num[len]:9;
  for(int i = 0; i <= limit; ++i) {
    if(preSix && i == 2 || i == 4) continue;
    result += dodfs(len-1, i == 6, limitR&&i==limit);
  }
  return result;
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

LL solve(LL n) {
  if(n == -1) return 0;
  int count = count_digit(n);
  return dodfs(count, false, true);
}

int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  LL start, end;
  while(scanf("%lld%lld", &start, &end) != EOF && (start || end)) {
    printf("%lld\n", solve(end) - solve(start-1));
  }
  return 0;
}
