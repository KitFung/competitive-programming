#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int arr[200005];

struct Node {
  int minv, maxv;
} node [400100];

int LC(int i) { return (i << 1); }
int RC(int i) { return (i << 1) + 1; }

void build() {
  memset(node, 0, sizeof(node));
}

void update(int L, int R, int idx, int pos, int value) {
  if(L == R) {
    node[idx].minv = node[idx].maxv = value;
    return;
  }
  int M = (L + R) >> 1;
  if(pos <= M) update(L, M, LC(idx), pos, value);
  if(pos > M) update(M+1, R, RC(idx), pos, value);

  node[idx].minv = min(node[LC(idx)].minv, node[RC(idx)].minv);
  node[idx].maxv = max(node[LC(idx)].maxv, node[RC(idx)].maxv);
}

int queryMin(int L, int R, int idx, int tL, int tR) {
  if(tL <= L && R <= tR) {
    return node[idx].minv;
  }
  int minv = 1 << 20;
  int M = (L + R) >> 1;
  if (tL <= M) minv = min(minv, queryMin(L, M, LC(idx), tL, tR));
  if (tR > M) minv = min(minv, queryMin(M+1, R, RC(idx), tL, tR));
  return minv;
}

int queryMax(int L, int R, int idx, int tL, int tR) {
  if(tL <= L && R <= tR) {
    return node[idx].maxv;
  }
  int maxv = -1;
  int M = (L + R) >> 1;
  if (tL <= M) maxv = max(maxv, queryMax(L, M, LC(idx), tL, tR));
  if (tR > M) maxv = max(maxv, queryMax(M+1, R, RC(idx), tL, tR));
  return maxv;
}

int main () {
  int N, Q, v, x, y;
  while(scanf("%d%d", &N, &Q) != EOF) {
    build();
    for(int i = 1; i <= N; ++i) {
      scanf("%d", &v);
      update(1, N, 1, i, v);
    }
    for(int i = 0; i < Q; ++i) {
      scanf("%d%d", &x, &y);
      printf("%d\n", queryMax(1, N, 1, x, y) - queryMin(1, N, 1, x, y));
    }
  }
  return 0;
}
