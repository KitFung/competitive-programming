#include <cstdio>
#include <cstring>

const int MAXN = 200000;
struct Edge {
  int val, next;
} edge[(MAXN << 1) + 100];
int edgeHead[MAXN + 100];

struct TreeNode {
  int low, high, sum;
} tnode[MAXN + 100];
int cidx = 0;
bool pick[MAXN + 100];
bool visited[MAXN + 100]; // avoid it give repeat edge in different direction
int n;

inline int lowbit(int x) {
  return x & (-x);
}

void dfs(int root) {
  tnode[root].low = ++cidx;
  visited[root] = true;
  for(int i = edgeHead[root]; i; i = edge[i].next)
    if(!visited[edge[i].val])
      dfs(edge[i].val);
  tnode[root].high = cidx;
}

// from bottom to top
void addToTree(int i, int v) {
  while(i <= n) {
    tnode[i].sum += v;
    i += lowbit(i);
  }
}

// from top to bottom
int sumFromTree(int i) {
  int sum = 0;
  while(i > 0) {
    sum += tnode[i].sum;
    i -= lowbit(i);
  }
  return sum;
}

void buildTree() {
  for(int i = 1; i <= n; ++i)
    addToTree(i, 1);
}

int main() {
  int a, b;
  scanf("%d", &n);
  buildTree();
  for(int i = 1; i < n; ++i) {
    scanf("%d%d", &a, &b);
    edge[i].val = b;
    edge[i].next = edgeHead[a];
    edgeHead[a] = i;
  }
  dfs(1);
  char s[3];
  int t, v;
  scanf("%d", &t);
  for(int i = 0; i < t; ++i) {
      scanf("%s%d", s, &v);
      if(s[0] == 'C') {
        if(pick[v]) {
          addToTree(tnode[v].low, 1);
          pick[v] = false;
        } else {
          addToTree(tnode[v].low, -1);
          pick[v] = true;
        }
      } else {
        printf("%d\n", sumFromTree(tnode[v].high) - sumFromTree(tnode[v].low - 1));
      }
  }
  return 0;
}
