#include <cstdio>
#include <cstring>


const int MAXN = 101;

int rc[MAXN][5];

int rv[5] = {1, 5, 10, 50, 100};

void create_rc() {
    memset(rc, 0, sizeof(rc));

    for(int i = 1; i < MAXN; ++i) {
        int tv = i;

        if(tv == 100) {
            rc[i][4] = 1;
            tv -= 100;
        }

        if(tv/10 == 9) {
            rc[i][2] = 1;
            rc[i][4] = 1;
            tv -= 90;
        }

        if(tv/10 == 4) {
            rc[i][2] = 1;
            rc[i][3] = 1;
            tv -= 40;
        }

        if(tv >= 50) {
            rc[i][3] += 1;
            tv -= 50;
        }

        if(tv >= 10) {
            int k = tv / 10;
            rc[i][2] = k;
            tv %= 10;
        }


        if(tv == 4) {
            rc[i][0] += 1;
            rc[i][1] += 1;
            tv -= 4;
        }

        if(tv == 9) {
            rc[i][0] += 1;
            rc[i][2] += 1;
            tv -= 9;
        }

        if(tv >= 5) {
            rc[i][1] += 1;
            tv -= 5;
        }

        rc[i][0] += tv;


        for(int j = 0; j < 5; ++j) {
            rc[i][j] += rc[i-1][j];
        }
    }

}

int main() {

    // freopen("input.txt", "r", stdin);

    create_rc();
    int n;
    while(scanf("%d", &n) != EOF && n != 0) {
        printf("%d: %d i, %d v, %d x, %d l, %d c\n", n, rc[n][0], rc[n][1], rc[n][2], rc[n][3], rc[n][4]);
    }

    return 0;
}
