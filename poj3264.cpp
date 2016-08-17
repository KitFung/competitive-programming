#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXN 50010

int cows[MAXN];
int st_min[MAXN][20], st_max[MAXN][20];
//http://noalgo.info/489.html

void initRMQ(int N) {
    for(int i = 0; i < N; ++i)
        st_max[i][0] = st_min[i][0] = cows[i];

    for(int j = 1; (1 << j) <= N; ++j)
        for(int i = 0; i + (1 << j) - 1< N; ++i) {
            st_max[i][j] = max(st_max[i][j-1], st_max[i+(1<<(j-1))][j-1]);
            st_min[i][j] = min(st_min[i][j-1], st_min[i+(1<<(j-1))][j-1]);
        }
}

int RMQ_max(int u, int v) {
    int k = log2(v - u + 1);
    return max(st_max[u][k], st_max[v-(1<<k)+1][k]);
}

int RMQ_min(int u, int v) {
    int k = log2(v - u + 1);
    return min(st_min[u][k], st_min[v-(1<<k)+1][k]);
}

int main() {
    // freopen("input.txt", "r", stdin);
    int N, Q;
    int A, B;

    while(scanf("%d%d", &N, &Q) != EOF) {
        for(int i = 0; i < N; ++i) scanf("%d", &cows[i]);

        initRMQ(N);

        for(int i = 0; i < Q; ++i) {
            scanf("%d%d", &A, &B);
            printf("%d\n", RMQ_max(A-1, B-1) - RMQ_min(A-1, B-1));
        }
    }

    return 0;
}