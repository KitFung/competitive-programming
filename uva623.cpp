#include <cstdio>
#include <cstring>
#include <cmath>

const int MAXN = 1001;

typedef struct CBIN {
    int num[3000];
    int size;
    CBIN() {
        size = 1;
        memset(num, 0, sizeof(num));
    }
} cbint;

cbint dp[1100];

cbint mult_bint(cbint arr, int n) {
    int carry = 0;
    cbint newbint;
    newbint.size = arr.size;

    for(int i = 0; i < arr.size; ++i) {
        int value = arr.num[i] * n + carry;
        newbint.num[i] = value % 10;
        carry = value / 10;
    }

    while (carry != 0) {
        newbint.size++;
        newbint.num[newbint.size - 1] = carry%10;
        carry /= 10;
    }

    return newbint;
}

void build_dp() {
    cbint a, b;
    dp[0].num[0] = 1;
    dp[1].num[0] = 1;

    for (int i = 2; i < MAXN; ++i) {
        dp[i] = mult_bint(dp[i - 1], i);
    }
}

void print_bint(int n) {
    for(int i = dp[n].size - 1; i >= 0; --i) {
        printf("%d", dp[n].num[i]);
    }
    printf("\n");
}

int main () {
    // freopen("input.txt", "r", stdin);
    int n;
    build_dp();
    while(scanf("%d", &n) != EOF) {
        printf("%d!\n", n);
        print_bint(n);
    }
    return 0;
}