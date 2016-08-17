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
int QRYhead[MAXN];
int parent[MAXN];
bool visited[MAXN];
int eidx, qidx;

bool isChild[MAXN];
int result[MAXN];

void init() {
    eidx = qidx = 0;
    memset(isChild, false, sizeof(isChild));
    memset(Ehead, -1, sizeof(Ehead));
    memset(QRYhead, -1, sizeof(QRYhead));
    memset(result, 0, sizeof(result));
    memset(visited, false, sizeof(visited));
}

void add_edge(int from, int to) {
    E[eidx].to = to;
    E[eidx].nxt = Ehead[from];
    Ehead[from] = eidx++;
}

void add_query(int from, int to) {
    QRY[qidx].to = to;
    QRY[qidx].nxt = QRYhead[from];
    QRYhead[from] = qidx++;

    QRY[qidx].to = from;
    QRY[qidx].nxt = QRYhead[to];
    QRYhead[to] = qidx++;
}

int find_parent(int x) {
    if(parent[x] != x)
        parent[x] = find_parent(parent[x]);
    return parent[x];
}

void Tarjan(int u) {

    parent[u] = u;

    for(int i = Ehead[u]; i != -1; i = E[i].nxt) {
        int v = E[i].to;
        Tarjan(v);
        parent[v] = u;
    }

    visited[u] = true;

    for(int i = QRYhead[u]; i != -1; i = QRY[i].nxt) {
        int v = QRY[i].to;
        if(!visited[v]) continue;

        result[find_parent(v)]++;
    }
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

        scanf("%d\n", &m);
        for(int i = 0; i < m; ++i) {
            scanf("(%d %d) ", &curNode, &toNode);
            add_query(curNode, toNode);
        }

        for(int i = 1; i <= n; ++i)
            if(!isChild[i])
                Tarjan(i);

        for(int i = 1; i <= n; ++i)
            if(result[i])
                printf("%d:%d\n", i, result[i]);
    }
    return 0;
}