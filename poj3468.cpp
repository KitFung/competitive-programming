#include <cstdio>
#include <cstring>

typedef long long LL;

LL arr[200005];

struct Node {
  LL sum, inc;
} node [400100];

int LC(LL i) { return (i << 1); }
int RC(LL i) { return (i << 1) + 1; }

void build(int L, int R, int idx) {
  if(L == R) {
    node[idx].sum = arr[L];
    return;
  }
  int M = (L + R) >> 1;
  build(L, M, LC(idx));
  build(M+1, R, RC(idx));
  node[idx].sum = node[LC(idx)].sum + node[RC(idx)].sum;
}

void pushDown(int idx, int L, int R) {
  int m = R-L+1;
  LL &inc = node[idx].inc;
  if(inc != 0) {
    node[LC(idx)].inc += inc;
    node[RC(idx)].inc += inc;
    node[LC(idx)].sum += inc * (m-(m>>1));
    node[RC(idx)].sum += inc * (m >> 1);
    inc = 0;
  }
}

void update(int L, int R, int idx, int tL, int tR, LL value) {
  if(tL <= L && R <= tR) {
    node[idx].sum += value*(R-L+1);
    node[idx].inc += value;
    return;
  }
  pushDown(idx, L, R);
  int M = (L + R) >> 1;
  if (tL <= M) update(L, M, LC(idx), tL, tR, value);
  if(tR > M) update(M+1, R, RC(idx), tL, tR, value);

  node[idx].sum = node[LC(idx)].sum + node[RC(idx)].sum;
}

LL query(int L, int R, int idx, int tL, int tR) {
  if(tL <= L && R <= tR) {
    return node[idx].sum;
  }
  LL total = 0;
  pushDown(idx, L, R);
  int M = (L + R) >> 1;
  if (tL <= M) total += query(L, M, LC(idx), tL, tR);
  if (tR > M) total += query(M+1, R, RC(idx), tL, tR);
  return total;
}

int main() {
  // freopen("input.txt", "r", stdin);
  int N, Q, a, b;
  LL c;
  char s[2];
  LL i;
  memset(node, 0, sizeof(node));
  scanf("%d%d", &N, &Q);
  for(int i = 1; i <= N; ++i) {
    scanf("%lld", &arr[i]);
  }
  build(1, N, 1);
  for(int i = 0; i < Q; ++i) {
    scanf("%s",s);
    if(s[0] == 'Q') {
      scanf("%d%d\n", &a, &b);
      printf("%lld\n", query(1, N, 1, a, b));
    } else {
      scanf("%d%d%lld\n", &a, &b, &c);
      update(1, N, 1, a, b, c);
    }
  }

  return 0;
}
