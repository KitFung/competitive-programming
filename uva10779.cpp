#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

const int INFI = 1 << 30;
const int MAXN = 201;
const int MIDN = 40;
const int MAXL = 5000;
const int START_PT = 0;
const int END_PT = 200;

struct Edge
{
    int to, cap, flow, next;
} E[MAXL];


int eidx;
int possible_v[MIDN];
int cleverManOwn[MIDN];
int adj[MAXN];
int allowed_map[MAXN];
map<int, int> sumofP;


void add_edge(int from, int to, int flow) {
    // printf("[from: %d  to: %d  flow: %d ]\n", from, to, flow);
    // printf("A\n");
    E[eidx].to = to;
    E[eidx].cap = flow;
    E[eidx].flow = 0;
    E[eidx].next = adj[from];
    adj[from] = eidx++;

    E[eidx].to = from;
    E[eidx].cap = 0;
    E[eidx].flow = 0;
    E[eidx].next = adj[to];
    adj[to] = eidx++;
    // printf("B\n");
}

bool bfs() {
    memset(allowed_map, -1, sizeof(allowed_map));
    queue<int> Q;
    Q.push(START_PT);
    allowed_map[START_PT] = 0;

    while(!Q.empty()) {
        int cur = Q.front(); Q.pop();
        // printf("... %d ...\n",  adj[cur]);
        for(int i = adj[cur]; i != -1; i  = E[i].next) {
            Edge &e = E[i];
            if(allowed_map[e.to] < 0 && e.flow < e.cap) {
                allowed_map[e.to] = allowed_map[cur] + 1;
                Q.push(e.to);
                if(e.to == END_PT)
                    return true;
            }
        }
    }
    return false;
}

int dfs(int cur, int end, int min_flow) {
    if(cur == end || min_flow == 0) return min_flow;

    int flow = 0, minf;
    for(int i = adj[cur]; i != -1; i  = E[i].next) {
        Edge &e = E[i];
        if(allowed_map[cur] + 1 == allowed_map[e.to] && (minf = dfs(e.to, end, min(min_flow, e.cap - e.flow)))) {
            flow += minf;
            e.flow += minf;
            E[i ^ 1].flow -= minf;
            min_flow -= minf;
            if(min_flow == 0) break;
        }
    }

    return flow;
}

int dinic() {
    int max_flow = 0;
    while(bfs()) {
        // printf("00-\n");
        max_flow += dfs(START_PT, END_PT, INFI);
    }
    // printf("---\n");
    return max_flow;
}

void get_input(int n, int m) {

    memset(possible_v, 0, sizeof(possible_v));
    memset(adj, -1, sizeof(adj));
    memset(cleverManOwn, 0, sizeof(cleverManOwn));
    eidx = 0;

    int k, v;

    scanf("%d", &k);
    for(int i = 0; i < k; ++i) {
        scanf("%d", &v);
        cleverManOwn[v]++;
    }

    for(int i = 1; i <= n - 1; ++i) {
        sumofP.clear();

        scanf("%d", &k);
        for(int j = 0; j < k; ++j) {
            scanf("%d", &v);
            if(sumofP.find(v) == sumofP.end())
                sumofP[v] = 1;
            else
                sumofP[v]++;
        }

        for(int j = 1; j <= m; ++j) {
            // if(sumofP.find(v) != sumofP.end())
            //     printf("|%d| %d\n", i, sumofP[j]);
            if(sumofP.find(v) != sumofP.end() && sumofP[j] > 0) {
                if(sumofP[j] > 1)
                    add_edge(i, j + MIDN, sumofP[j] - 1);
            } else {
                add_edge(j + MIDN, i, 1);
            }

        }
    }

    for(int i = 1; i <=  m; ++i) {
        if (cleverManOwn[i] > 0) {
            add_edge(START_PT, i + MIDN, cleverManOwn[i]);
        }
        add_edge(i + MIDN, END_PT, 1);
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T;
    int n, m;

    scanf("%d", &T);
    for(int i = 1; i <= T; ++i) {
        scanf("%d%d", &n, &m);
        get_input(n, m);
        printf("Case #%d: %d\n", i, dinic());
    }

    return 0;
}