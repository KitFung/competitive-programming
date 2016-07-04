#include <bits/stdc++.h>
using namespace std;

const int N = 110 + 5;
const int M = 5e4 + 5;
const int INF = 0x3f3f3f3f;
char ori[N], fin[N];
int dp[M];
int cnt[6];
int g[6][6];

// 6-base to 10-base
int idx(int *c) {
    int ret = 0;
    for (int i=0; i<6; ++i)  {
        ret = ret * 6 + c[i];
    }
    return ret;
}

// 10-base to 6-base
void ridx(int x, int *c)    {
    for (int i=5; i>=0; --i) {
        c[i] = x % 6;
        x /= 6;
    }
}

// 一個6位的6進制列陣, 012345到任意6進制的6位數所需要的步數
void BFS(void)  {
    memset (dp, INF, sizeof (dp));
    int c[6];
    for (int i=0; i<6; ++i)  c[i] = i;   //nomal, not change | 012345
    int s = idx (c);    dp[s] = 0;       // s = 1865
    queue<int> que;   que.push (s);
    while (!que.empty ())   {
        int u = que.front ();   que.pop ();
        ridx (u, c);                    // change from 10-base to 6-base
        for (int i=0; i<6; ++i)  {
            for (int j=0; j<6; ++j)  {
                int t[6];
                memcpy (t, c, sizeof (t));
                for (int k=0; k<6; ++k)  {
                    if (t[k] == i)  t[k] = j; // change all the number i to j
                }
                int v = idx (t);         // change from 6-base to 10-base
                if (dp[v] > dp[u] + 1)   {
                    dp[v] = dp[u] + 1;
                    que.push (v);
                }
            }
        }
    }
}

int main(void)  {
    BFS ();
    while (scanf ("%s%s", ori, fin) == 2)   {
        int len = strlen (ori);
        memset (cnt, 0, sizeof (cnt));
        memset (g, 0, sizeof (g));
        for (int i=0; i<len; ++i)    {
            int d1 = fin[i] - '1', d2 = ori[i] - '1';
            cnt[d1]++;  g[d1][d2]++;
        }
        int ans = INF;
        int c[6];
        for (int i=0; i<M; ++i)  {
            ridx (i, c);            // i 的 六進制表示
            int tmp = dp[i];        // 先做一次第2種的轉換 由 i 到 012345 的步數
            for (int j=0; j<6; ++j)  {   // j 在 cnt 是數值, 在 c 是數位
                tmp += cnt[j] - g[j][c[j]];  // There are cnt[j] amount of j which occur in target string
                                             // g[j][c[j]] will need to transform from c[j]
                                             // 只要細想,第二種方法最多只需用六次,就可以得出所有可以靠第二種方法得出的結果
                                             // dp[ idx({0, 1, 2, 3, 4, 5})] = 0, 因為他表示把所有 0轉到0, 1轉到1
                                             // dp[ idx({0, 0, 0, 0, 0, 0})] 表示把所有 0轉到0, 1轉到0
                                             // the remain should be the amount that need to transform using method 1. transforn 1 by 1
            }
            ans = min (ans, tmp);
        }
        printf ("%d\n", ans);
    }

    return 0;
}
