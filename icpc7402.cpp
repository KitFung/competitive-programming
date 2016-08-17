#include <cstdio>
#include <cstring>
#include <set>
using namespace std;

#define LC (idx<<1)
#define RC (idx<<1)+1

const int MAXN = 100100;
struct Edge {
  int val, next;
} edge[MAXN];

int edgeHead[MAXN];
int cidx;
bool visited[MAXN];
int color[MAXN];

int [MAXN];

struct TreeNode {
    int low, high;
} node[MAXN];

struct SegmentTree {
    set<int> color;
} stnode[MAXN << 1];

void dfs(int root) {
  node[root].low = ++cidx;
  visited[root] = true;
  for(int i = edgeHead[root]; i != -1; i = edge[i].next)
    if(!visited[edge[i].val])
      dfs(edge[i].val);
  node[root].high = cidx;
}

void build(int L, int R, int idx) {
  if(L == R) {
    stnode[idx].color.clear();
    stnode[idx].color.insert(color[node[L].high]);
    return;
  }
  int M = (L + R) >> 1;
  build(L, M, LC);
  build(M+1, R, RC);

  stnode[idx].color.clear();
  stnode[idx].color.insert(stnode[LC].color.begin(), stnode[LC].color.end());
  stnode[idx].color.insert(stnode[RC].color.begin(), stnode[RC].color.end());
}

void pushDown()

void pullUp(int idx, int L, int R) {
  stnode[idx].color.clear();
  stnode[idx].color.insert(stnode[LC].color.begin(), stnode[LC].color.end());
  stnode[idx].color.insert(stnode[RC].color.begin(), stnode[RC].color.end());
}

void update(int L, int R, int idx, int tL, int tR, int value) {

}


void add_edge(int i, int from, int to) {
    edge[i].val = to;
    edge[i].next = edgeHead[from];
    edgeHead[from] = i;
}

int main() {
    int T;
    int N, M;
    scanf("%d", &T);

    for(int nt = 1; nt <= T; ++nt) {
        memset(edgeHead, -1, sizeof(edgeHead));
        memset(visited, false, sizeof(visited));
        cidx = 0;

        scanf("%d", &N);
        int from, to;
        for(int i = 1; i < N; ++i) {
            scanf("%d%d", &from, &to);
            add_edge(i, from, to);
        }

        for(int i = 1; i <= N; ++i) {
            scanf("%d", &color[i]);
        }

        dfs(1);
        build(1, N, 1);


    }
    return 0;
}