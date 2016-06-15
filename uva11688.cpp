#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

typedef struct node {
  int left, right;
  node() {}
} Node;

Node nodes[MAXN];

int maxH[MAXN];
int parent[MAXN];
int dp[MAXN];

int getHeight(int nodeno) {
  if(maxH[nodeno] != -1)
    return maxH[nodeno];
  if(nodeno == 0)
    return 0;
  Node &no = nodes[nodeno];
  int lefth = getHeight(no.left);
  int righth = getHeight(no.right);
  maxH[nodeno] = 1 + max(lefth, righth);
  return maxH[nodeno];
}

void dfs(int curno, int lh, int rh, int lc, int rc) {
  if(curno == 0)
    return;

  int lsh = getHeight(nodes[curno].left);
  int rsh = getHeight(nodes[curno].right);

  dp[curno] = max( max(lh, rh), max(lsh + lc, rsh + rc)) + 1;
  dfs(nodes[curno].left, lh, max(rh, rsh + rc + 1), lc, rc+1);
  dfs(nodes[curno].right, max(lh, lsh + lc + 1), rh, lc+1, rc);
}


int main() {
  // freopen("input.txt", "r", stdin);

  int n;
  int root, leftest, rightest;
  int rootH = 0;

  while(scanf("%d", &n) != EOF && n) {
    memset(parent, 0, sizeof(parent));

    for(int i = 1; i <= n; ++i) {
      scanf("%d%d", &nodes[i].left, &nodes[i].right);
      parent[nodes[i].left] = i;
      parent[nodes[i].right] = i;
    }

    memset(maxH, -1, sizeof(maxH));
    for(int i = 1; i <= n; ++i)
      if(parent[i] == 0) {
        root = i;
        dfs(root, 0, 0, 0, 0);
        break;
      }

    for(int i = 1; i <= n; ++i)
      printf("%d\n", dp[i]);
  }

  return 0;
}
