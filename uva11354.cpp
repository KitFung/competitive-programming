#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXEDGE 100010
#define MAXNODE 50010
#define MAXDEPTH 20

struct Edge {
    int from, to, w;
    Edge() {}
    Edge(int x, int y, int z): from(x), to(y), w(z) {}
    bool operator < (const Edge &b) const {
        return w > b.w;
    }
};

struct PointTo {
    int to, w;
    PointTo() {}
    PointTo(int x, int y): to(x), w(y) {}
};

priority_queue<Edge> E;

vector<PointTo> P[MAXNODE];
int parent[MAXNODE];

int djs_find(int x) {
    if(parent[x] < 0) return x;
    return parent[x] = djs_find(parent[x]);
}

void djs_set(int x, int y) {
    parent[x] += parent[y];
    parent[y] = x;
}

bool djs_join(int x, int y) {
    int vx = djs_find(x);
    int vy = djs_find(y);
    if(vx == vy) return false;

    if(parent[vx] < parent[vy]) {
        djs_set(vx, vy);
    } else {
        djs_set(vy, vx);
    }

    return true;
}

void Kruscal() {
    memset(parent, -1, sizeof(parent));

    while(!E.empty()) {
        Edge e = E.top(); E.pop();
        if(djs_join(e.from, e.to)) {
            P[e.from].push_back(PointTo(e.to, e.w));
            P[e.to].push_back(PointTo(e.from, e.w));
        }
    }
}


int fathers[MAXNODE][MAXDEPTH];
int dp[MAXNODE][MAXDEPTH];
int depth[MAXNODE];
void dfs(int x, int father, int weight) {
    depth[x] = depth[father]+1; fathers[x][0] = father; dp[x][0] = weight;
    for(int i = 1; i < MAXDEPTH; ++i) {
        fathers[x][i] = fathers[fathers[x][i-1]][i-1];
        dp[x][i] = max(dp[x][i-1], dp[fathers[x][i-1]][i-1]);
    }

    for(int i = 0; i < P[x].size(); ++i) {
        PointTo &e = P[x][i];
        if(e.to != father) dfs(e.to, x, e.w);
    }
}

int max_w_through_lca(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    int max_w = 0;

     int tu = u, tv = v;
    for(int i = 0; diff; ++i, diff >>= 1)
        if(diff&1) {
            max_w = max(max_w, dp[tu][i]);
            tu = fathers[tu][i];
        }
    if(tu == tv) return max_w;

    for(int i = MAXDEPTH-1; i >= 0; --i)
        if(fathers[tu][i] != fathers[tv][i]) {
            max_w = max(max_w, dp[tu][i]);
            max_w = max(max_w, dp[tv][i]);
            tu = fathers[tu][i];
            tv = fathers[tv][i];
        }
    max_w = max(max_w, dp[tu][0]);
    max_w = max(max_w, dp[tv][0]);

    return max_w;
}


int main() {
    // freopen("input.txt", "r", stdin);

    int cities, roads;
    int x, y, d;
    int nquery, from, to;
    int ncase = 0;

    while(scanf("%d%d", &cities, &roads) != EOF) {

        if(ncase++ > 0) printf("\n");

        for(int i = 0; i <= cities; ++i)
            P[i].clear();

        for(int i = 0; i < roads; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            E.push(Edge(x, y, d));
        }
        Kruscal();

        depth[0] = 0;
        dfs(1, 0, 0);

        scanf("%d", &nquery);
        for(int i = 0; i < nquery; ++i) {
            scanf("%d%d", &from, &to);
            printf("%d\n", max_w_through_lca(from, to));
        }

    }
    return 0;
}