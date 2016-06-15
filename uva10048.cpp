#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int INFT = 1 << 29;
const int MAXN = 101;

int station[MAXN];
int adj[MAXN][MAXN];
bool visited[MAXN];

int djk_algo(int n, int from, int to) {

    for(int i = 1; i <= n; ++i) station[i] = INFT;

    station[from] = 0;
    memset(visited, false, sizeof(visited));

    for(int i = 0; i < n; ++i) {
        int a = -1, minv = INFT;

        for(int j = 1; j <= n; ++j) {
            if(!visited[j] && station[j] < minv) {
                minv = station[j];
                a = j;
            }
        }

        if(a == -1) break;
        visited[a] = true;

        for(int j = 1; j <= n; ++j) {
            if(visited[j] || adj[a][j] == INFT) continue;
            int v = max(station[a], adj[a][j]);
            if(v < station[j]) {
                station[j] = v;
            }
        }

    }

    return station[to];
}


int main() {

    int C, S, Q;
    int count = 1;
    while(scanf("%d%d%d", &C, &S, &Q) != EOF && ( C || S || Q )) {
        for(int i = 1; i <= C; ++i) {
            for(int j = 1; j <= C; ++j) {
                adj[i][j] = INFT;
                adj[j][i] = INFT;
            }
        }

        for(int i = 0; i < S; ++i) {
            int c1, c2, d;
            scanf("%d%d%d", &c1, &c2, &d);
            adj[c1][c2] = d;
            adj[c2][c1] = d;
        }

        if(count > 1) printf("\n");
        printf("Case #%d\n", count++);

        for(int i = 0; i < Q; ++i) {
            int from, to;
            scanf("%d%d", &from, &to);

            int result = djk_algo(C, from, to);
            if(result != INFT) {
                printf("%d\n", result);
            } else {
                printf("no path\n");
            }
        }

    }
    return 0;
}