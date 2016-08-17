#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXN 1000
#define DEG 15

struct edge {
    int to, nxt;
} E[MAXN*1000];
int Ehead[MAXN];
int result[MAXN];
int eidx;

bool isChild[MAXN];


void add_edge(int from, int to) {
    E[eidx].to = to;
    E[eidx].nxt = Ehead[from];
    Ehead[from] = eidx++;
}

int D[MAXN << 1];
int first[MAXN];
int depth[MAXN << 1];
int dp[MAXN << 1][DEG];
int idx;
void dfs(int u, int dep) {
    D[++idx] = u;
    depth[idx] = dep;
    first[u] = idx;

    for(int i = Ehead[u]; i != -1; i = E[i].nxt) {
        int to = E[i].to;
        dfs(to, dep + 1);

        D[++idx] = u;
        depth[idx] = dep;
    }
}

void RMQ_init(int N) {
    for(int i = 1; i <= N; ++i) dp[i][0] = i;

    for(int j = 1; (1 << j) <= N; ++j)
        for(int i = 1; i + (1<<j) - 1 <= N; ++i)
            dp[i][j] =  depth[dp[i][j-1]]<depth[dp[i+(1<<(j-1))][j-1]]?
                dp[i][j-1]:dp[i+(1<<(j-1))][j-1];
}

int RMQ_min(int u, int v) {
    if(v < u) swap(u, v);
    int k = log2(v - u + 1);
    return depth[dp[u][k]]<depth[dp[v-(1<<k)+1][k]]?
            dp[u][k]:dp[v-(1<<k)+1][k];
}


void init() {
    eidx = 0;
    idx = 0;
    memset(isChild, false, sizeof(isChild));
    memset(Ehead, -1, sizeof(Ehead));
    memset(result, 0, sizeof(result));
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
            if(!isChild[i]) {
                dfs(i, 0);
                break;
            }

        RMQ_init(n*2);

        scanf("%d\n", &m);
        for(int i = 0; i < m; ++i) {
            scanf("(%d %d) ", &curNode, &toNode);
            int lca = D[RMQ_min(first[curNode], first[toNode])];
            result[lca]++;
        }

        for(int i = 1; i <= n; ++i)
            if(result[i])
                printf("%d:%d\n", i, result[i]);

    }
    return 0;
}