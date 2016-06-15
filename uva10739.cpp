#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

char word[1100];
int dp[1100][1100];


int find_ans() {
    memset(dp, 0, sizeof(dp));
    int len = strlen(word);

    for(int i = len - 1; i >= 0; --i) {
        for(int j = i + 1; j < len; ++j) {
            if(word[j] == word[i])
                dp[i][j] = dp[i + 1][j - 1];
            else {
                dp[i][j] = std::min(dp[i + 1][j], dp[i][j - 1]);
                dp[i][j] = std::min(dp[i][j], dp[i + 1][j - 1]);
                dp[i][j] += 1;
            }
        }
    }
    return dp[0][len - 1];
}

int main() {
    // freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i ){
        scanf("%s", word);

        printf("Case %d: %d\n", i, find_ans());
    }
    return 0;
}
