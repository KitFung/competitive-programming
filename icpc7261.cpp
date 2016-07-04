#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN = 10010;

struct Grid {
  LL w, h, x;
} g[MAXN];

LL areaBeforeX(LL n, LL x) {
  LL tmp = 0;
  for(int i = 0; i < n; i++)
  {
      tmp += g[i].h * max(0LL, min(g[i].w, x - g[i].x));
  }
  return tmp;
}

// Left half need to >= Right half
int main() {
  // freopen("input.txt", "r", stdin);
  LL R, L, T, W, H, sum;
  int ncase , N;
  scanf("%d", &ncase);

  for(;ncase-- > 0;) {
    sum = 0;
    scanf("%lld%d", &R, &N);
    for(int n = 0; n < N; ++n) {
      scanf("%lld%lld%lld%lld", &L, &T, &W, &H);
      g[n].x = L;
      g[n].w = W;
      g[n].h = H;
      sum += (LL)(W * H);
    }

    LL left = 0, right = R + 1, mid;
    while(left < right) {
      mid = (left + right)/2;
      if(areaBeforeX(N, mid) * 2 < sum)
        left = mid + 1;
      else
        right = mid;
    }

    LL ans = areaBeforeX(N, right);
    left = 0, right = R + 1;
    while(left < right) {
      mid = (left + right)/2;
      if(areaBeforeX(N, mid) <= ans)
        left = mid + 1;
      else
        right = mid;
    }

    printf("%lld\n", left-1);
  }

  return 0;
}
