#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int INFT = 1 << 30;
const int MAXN = 101;
int road[MAXN][MAXN];
int station[MAXN];
bool visited[MAXN];

int djk_algo(int n, int from, int to) {
    memset(station, 0, sizeof(station));
    memset(visited, false, sizeof(visited));
    station[from] = INFT;

    for (int k = 0; k < n; ++k) {
        int a = -1, maxv = 0;
        for (int i = 1; i <= n; ++i) {
            if (!visited[i] && station[i] > maxv) {
                a = i;
                maxv = station[i];
            }
        }

        if (a == -1) break;
        visited[a] = true;

        for (int i = 1; i <= n; ++i) {
            if (visited[i] || road[a][i] == INFT) continue;
            int value = min(station[a], road[a][i]);
            if (value > station[i]) {
                station[i] = value;
            }
        }
    }

    return station[to];
}


int main() {

    int N, R;
    int c1, c2, p;
    int from, to, amount;
    int count = 0;

    while (scanf("%d%d", &N, &R) != EOF && (N || R)) {
        memset(road, 0, sizeof(road));
        for (int i = 0; i < R; ++i) {
            scanf("%d%d%d", &c1, &c2, &p);
            road[c1][c2] = p - 1;
            road[c2][c1] = p - 1;
        }

        scanf("%d%d%d", &from, &to, &amount);

        int cost = djk_algo(N, from, to);
        cost = (int)(ceil((double)amount/cost));

        printf("Scenario #%d\n", ++count);
        printf("Minimum Number of Trips = %d\n\n", cost);
    }
    return 0;
}
