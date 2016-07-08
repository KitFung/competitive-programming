#include <cstdio>
#include <cstring>

int arr[200005];

struct Node {
  int sum;
} node [400100];

int LC(int i) { return (i << 1); }
int RC(int i) { return (i << 1) + 1; }

void build() {
  memset(node, 0, sizeof(node));
}

void update(int L, int R, int idx, int pos, int value) {
  if(L == R) {
    node[idx].sum = value;
    return;
  }
  int M = (L + R) >> 1;
  if(pos <= M) update(L, M, LC(idx), pos, value);
  if(pos > M) update(M+1, R, RC(idx), pos, value);

  node[idx].sum = node[LC(idx)].sum + node[RC(idx)].sum;
}

int query(int L, int R, int idx, int tL, int tR) {
  if(tL <= L && R <= tR || node[idx].sum == 0) {
    return node[idx].sum;
  }
  int total = 0;
  int M = (L + R) >> 1;
  if (tL <= M) total += query(L, M, LC(idx), tL, tR);
  if (tR > M) total += query(M+1, R, RC(idx), tL, tR);
  return total;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout)
  int n, tmp, x, y;
  int count = 1;
  char command[5];
  while(scanf("%d", &n) != EOF) {
    build();

    if(count != 1) printf("\n");
    printf("Case %d\n", count++);

    for(int i = 1; i <= n; ++i) {
      scanf("%d", &tmp);
      update(1, n, 1, i, tmp);
    }
    while(scanf("%s", command) && command[0] != 'E') {
      scanf("%d%d", &x, &y);
      if(command[0] == 'S') {
        update(1, n, 1, x, y);
      }
      if(command[0] == 'M') {
        printf("%d\n", query(1, n, 1, x, y));
      }
    }
  }

  return 0;
}
