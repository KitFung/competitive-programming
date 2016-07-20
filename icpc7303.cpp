#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define left 0
#define topside 1
#define right 2
#define bot 3

const int MAXG = 105;

int djs[80005];
char inc[105][105];

typedef struct edge {
  int from, to, cost;
  edge() {}
  edge(int x, int y, int z): from(x), to(y), cost(z) {}
  bool operator < (const edge& b) const {
    return cost > b.cost;
  }
} Edge;

priority_queue<Edge> Q;
int row, col;

int djs_find(int a) {
  if(djs[a] < 0)
    return a;
  else
    return djs[a] = djs_find(djs[a]);
}

void djs_set(int a, int b) {
  djs[a] += djs[b];
  djs[b] = a;
}

bool djs_join(int a, int b) {
  int va = djs_find(a);
  int vb = djs_find(b);
  if(va == vb) return false;
  if(va < vb) {
    djs_set(va, vb);
  } else {
    djs_set(vb, va);
  }
  return true;
}

inline bool validXY(int x, int y) {
  return x < col && y < row;
}

inline int diridx(int x, int y, int dir) {
  int nidx = (x + y*col) << 2;
  return nidx+dir;
}

void add_edge(char w, int x, int y, int cost) {
  if(w == '/') {
    djs_join(diridx(x, y, topside), diridx(x, y, left));
    djs_join(diridx(x, y, right), diridx(x, y, bot));
    Q.push(
      Edge(diridx(x, y, topside), diridx(x, y, right), cost)
    );
    Q.push(
      Edge(diridx(x, y, left), diridx(x, y, bot), cost)
    );
  } else {
    djs_join(diridx(x, y, topside), diridx(x, y, right));
    djs_join(diridx(x, y, left), diridx(x, y, bot));
    Q.push(
      Edge(diridx(x, y, topside), diridx(x, y, left), cost)
    );
    Q.push(
      Edge(diridx(x, y, right), diridx(x, y, bot), cost)
    );
  }
}

void add_common_edge() {
  for(int r = 0; r < row; ++r) {
    for(int c = 0; c < col; ++c) {
      if(c != col-1) {
        djs_join(diridx(c, r, right), diridx(c+1, r, left));
      }
      if(r != row-1) {
        djs_join(diridx(c, r, bot), diridx(c, r+1, topside));
      }
    }
  }
}

int do_djs() {
  int sum = 0;
  while(!Q.empty()) {
    Edge e = Q.top(); Q.pop();
    if(djs_join(e.from, e.to)) {
      sum += e.cost;
    }
  }
  return sum;
}

char line[105];
int main() {
  int N, cost;
  scanf("%d", &N);

  for(int ncase = 1; ncase <= N; ++ncase) {
    memset(djs, -1, sizeof(djs));

    scanf("%d%d", &row, &col);
    for(int r = 0; r < row; ++r) {
      scanf("%s", line);
      for(int c = 0; c < col; ++c) {
        inc[c][r] = line[c];
      }
    }

    for(int r = 0; r < row; ++r) {
      for(int c = 0; c < col; ++c) {
        scanf("%d", &cost);
        add_edge(inc[c][r], c, r, cost);
      }
    }

    add_common_edge();
    printf("Case %d: %d\n", ncase, do_djs());
  }
  return 0;
}
