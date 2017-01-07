#include <cstdio>
#include <cstring>

#define MAXN 14
#define MOD 100000000
#define MAXSTATE 1000


int M, N;
int nstate, state[MAXSTATE];
int row[MAXN];
int dp[MAXN][MAXSTATE];


void init() {
    memset(dp, 0, sizeof(dp));
    nstate = 0 ;
    for(int i = 0; i < (1<<N); ++i)
        if((i & (i << 1)) == 0)
            state[nstate++] = i;
}

int main() {
    // freopen("input.txt", "r", stdin);
    while(scanf("%d%d", &M, &N) != EOF) {
        init();

        for(int i = 0; i < M; ++i) {
            row[i] = 0;
            for(int j = N-1; j >= 0; --j) {
                int t;
                scanf("%d", &t);
                row[i] += t << j;
            }
        }

        for(int i = 0; i < nstate; ++i)
            dp[0][i] = ((row[0] & state[i]) == state[i])?1:0; // this state is compatiabilite to first row


        for(int i = 1; i < M; ++i)
            for(int j = 0; j < nstate; ++j)
                if((row[i] & state[j]) == state[j])
                    for(int j2 = 0; j2 < nstate; ++j2)
                        if((state[j] & state[j2]) == 0)
                            dp[i][j] = (dp[i][j] + dp[i-1][j2])%MOD;

        int cnt = 0;
        for (int i = 0; i < nstate; ++i)
            cnt = (cnt+dp[M-1][i])%MOD;

        printf("%d\n", cnt);
    }
    return 0;
}