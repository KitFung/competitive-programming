#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXN 1000
#define DEG 15

struct edge {
    int to, nxt;
} E[MAXN*1000], QRY[MAXN*1000];
int Ehead[MAXN];
int deep[MAXN], father[MAXN][DEG];
int eidx;

bool isChild[MAXN];
int result[MAXN];

void init() {
    eidx = 0;
    memset(isChild, false, sizeof(isChild));
    memset(Ehead, -1, sizeof(Ehead));
    memset(result, 0, sizeof(result));
}

void add_edge(int from, int to) {
    E[eidx].to = to;
    E[eidx].nxt = Ehead[from];
    Ehead[from] = eidx++;
}

void BFS(int root) {
    queue<int> Q;
    deep[root] = 0;
    father[root][0] = root;
    Q.push(root);

    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int i = 1; i < DEG; ++i)
            father[u][i] = father[father[u][i-1]][i-1];
        for(int i = Ehead[u]; i != -1; i = E[i].nxt) {
            int v = E[i].to;
            deep[v] = deep[u] + 1;
            father[v][0] = u;
            Q.push(v);
        }
    }
}

// v is deeper
int LCA(int u, int v) {
    if(deep[u] > deep[v]) swap(u, v);
    int hv = deep[v], hu = deep[u];
    int tu = u, tv = v;
    // raise v to same deep as u
    for(int diff = hv - hu, i = 0; diff; ++i, diff>>=1)
        if(diff&1) // 5 = 101 = 2^0 + 2^2
            tv = father[tv][i];

    if(tu==tv) return tu;

    // raise both u and v and find the intersect point
    for(int i = DEG-1; i >= 0; --i) {
        if(father[tu][i] == father[tv][i]) continue;
        tu = father[tu][i];
        tv = father[tv][i];
    }
    return father[tu][0];
}


int main() {
    // freopen("input.txt", "r", stdin);
    int n, m, curNode, toNode, ntoNode;

    while(scanf("%d", &n) != EOF) {
        init();

        for(int i = 0; i < n ;++i) {
            scanf("%d:(%d)", &curNode, &ntoNode);

            for(int i2 = 0; i2 < ntoNode; ++i2) {
                scanf("%d", &toNode);
                add_edge(curNode, toNode);
                isChild[toNode] = true;
            }
        }

        for(int i = 1; i <= n; ++i)
            if(!isChild[i])
                BFS(i);

        scanf("%d\n", &m);
        for(int i = 0; i < m; ++i) {
            scanf("(%d %d) ", &curNode, &toNode);
            int lca = LCA(curNode, toNode);
            result[lca]++;
        }

        for(int i = 1; i <= n; ++i)
            if(result[i])
                printf("%d:%d\n", i, result[i]);

    }
    return 0;
}