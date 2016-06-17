#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
// This is not correct solution

const int INFI = 1 << 30;
const int MAXN = 10001;

typedef struct road {
  int from, to, cost;
  road() {}
  road(int x, int y, int z): from(x), to(y), cost(z) {}
} Road;

struct roadcmp {
  bool operator() (const Road &a, const Road &b) {
    return a.cost > b.cost;
  }
};

int djs[MAXN];
bool isinMST[MAXN][MAXN];
int road_map[MAXN][MAXN];
int weight[MAXN];
bool visited[MAXN];

vector<Road> inputs;
priority_queue<Road, vector<Road>, roadcmp> all_road;



int djs_find(int a) {
  if(djs[a] < 0)
    return a;
  else
    return djs[a] = djs_find(djs[a]);
}

void djs_setv(int a, int b) {
  djs[a] += djs[b];
  djs[b] = a;
}

void djs_union(int a, int b) {
  int va = djs_find(a);
  int vb = djs_find(b);
  if(va == vb) return;
  if(djs[va] > djs[vb]) {
    djs_setv(vb, va);
  } else {
    djs_setv(va, vb);
  }
}

void build_mst(int n) {
  int count = 0;
  while(!all_road.empty()) {
    Road curpoint = all_road.top(); all_road.pop();
    int f  = curpoint.from;
    int t = curpoint.to;

    if(djs_find(f) != djs_find(t)) {
      djs_union(f, t);
      isinMST[f][t] = isinMST[f][t] = true;
      count++;
    }
    if(count == n) return;
  }
}

// shortest distance
int next_min_line_val(int pointa, int pointb, int n) {
  memset(visited, false, sizeof(visited));

  int c = road_map[pointa][pointb];
  road_map[pointa][pointb] = road_map[pointb][pointa] = -1;

  for(int i = 0; i <= n; ++i) weight[i] = INFI;

  weight[pointa] = 0;
  for(int k = 0; k < n; ++k) {
    int a = -1, minv = INFI;
    for(int i = 1; i <= n; ++i) {
      if(!visited[i] && weight[i] < minv) {
        a = i;
        minv = weight[i];
      }
    }

    if(a == -1) break;
    visited[a] = true;

    for(int i = 1; i <= n; ++i) {
      if(i == a || visited[i] || road_map[a][i] == -1) continue;
      if(max(weight[a], road_map[a][i]) < weight[i]) {
        weight[i] = max(weight[a], road_map[a][i]);
      }
    }
  }

  road_map[pointa][pointb] = road_map[pointb][pointa] = c;

  return weight[pointb]==INFI?-1:weight[pointb];
}



int main() {
  // freopen("input.txt", "r", stdin);
  int ncase;
  int n, m;
  int f, t, c;
  scanf("%d", &ncase);

  for(int k = 0; k < ncase; ++k) {
    scanf("%d%d", &n, &m);

    inputs.clear();
    all_road = priority_queue<Road, vector<Road>, roadcmp>();
    memset(road_map, -1, sizeof(road_map));
    memset(isinMST, false, sizeof(isinMST));
    memset(djs, -1, sizeof(djs));

    for(int i = 0; i < m; ++i) {
      scanf("%d%d%d", &f, &t, &c);

      inputs.push_back(Road(f, t, c));
      all_road.push(Road(f, t, c));
      road_map[f][t] = road_map[t][f] = c;
    }

    build_mst(n);
    int total_v = 0;
    for(int i = 1; i <= m; ++i) {
      int from = inputs[i - 1].from;
      int to = inputs[i - 1].to;
      int cost = inputs[i - 1].cost;
      int a = -1, b = -1;
      int minv = next_min_line_val(from, to, n);

      if(minv != -1)
        if(isinMST[from][to])
          a = abs(minv - cost);
        else
          b = abs(minv - cost);

      total_v += i * a + i * i * b;
    }

    printf("Case %d: %d\n", k+1, total_v);
  }

  return 0;
}
