#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;


#define MAXM 2010
#define MAXN 1010
#define INFI (1<<30)

int eidx;
struct Edge {
    int to, nxt;
} E[MAXM];
int head[MAXM];

int cost[MAXN];

void add_edge(int from, int to) {
    E[eidx].to = to;
    E[eidx].nxt = head[from];
    head[from] = eidx++;
}


int groupIdx;
int numIdx;
int num[MAXN], low[MAXN], instack[MAXN], belong[MAXN];
int indeg[MAXN];
int min_cost[MAXN];
stack<int> S;


void tarjan(int u) {
    num[u] = low[u] = ++numIdx;
    S.push(u);

    for(int i = head[u]; i != -1; i = E[i].nxt) {
        int v = E[i].to;
        if(!num[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(!belong[v]) {
            low[u] = min(low[u], num[v]);
        }
    }

    if(low[u] == num[u]) {

        groupIdx++;
        while(true) {
            int v = S.top(); S.pop();
            belong[v] = groupIdx;
            min_cost[groupIdx] = min(min_cost[groupIdx], cost[v]);
            if(u == v) break;
        }
    }
}

void init() {
    eidx = 0;
    groupIdx = numIdx = 0;
    memset(head, -1, sizeof(head));
    memset(indeg, 0, sizeof(indeg));
    memset(belong, 0, sizeof(belong));
}

int main () {
    // freopen("input.txt", "r", stdin);


    int peoples, contacts;
    int X, Y;

    while(scanf("%d%d", &peoples, &contacts) != EOF) {
        init();

        for(int i = 1; i <= peoples; ++i) scanf("%d", &cost[i]);
        for(int i = 1; i <= contacts; ++i) {
            scanf("%d%d", &X, &Y);
            add_edge(X, Y);
        }

        for(int i = 1; i <= peoples; ++i) min_cost[i] = INFI;

        for(int i = 1 ; i <= peoples; ++i)
            if(!num[i]) {
                tarjan(i);
            }

        for(int u = 1; u <= peoples; ++u)
            for(int i = head[u]; i != -1; i = E[i].nxt) {
                int v = E[i].to;
                if(belong[u] != belong[v]) {
                    indeg[belong[v]]++;
                }
            }

        int count = 0, sum = 0;
        for(int i = 1; i <= groupIdx; ++i)
            if(indeg[i] == 0) {
                count++;
                sum += min_cost[i];
            }

        printf("%d %d\n", count, sum);

    }

    return 0;
}