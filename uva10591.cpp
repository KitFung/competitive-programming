#include <cstdio>
#include <cmath>
#include <cstring>

bool visited[1000]; // The sum of digit of 10^9 must < 1000;

int sum_of_square_digit(int number) {
    int sum = 0;
    int tnum = number;
    int tmp;

    while(tnum > 0) {
        tmp = tnum%10;
        sum += tmp * tmp;
        tnum /= 10;
    }
    sum += tnum * tnum;
    return sum;
}

bool ishappy(int number) {
    memset(visited, false, sizeof(visited));

    int tnum = number;

    tnum = sum_of_square_digit(tnum);
    while(!visited[tnum]) {
        visited[tnum] = true;
        if(tnum == 1) return true;

        tnum = sum_of_square_digit(tnum);
    }

    return false;
}

int main() {
    // freopen("input.txt", "r", stdin);
    int n, v;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &v);
        bool result = ishappy(v);

        if(result) {
            printf("Case #%d: %d is a Happy number.\n", i, v);
        } else {
            printf("Case #%d: %d is an Unhappy number.\n", i, v);
        }
    }
    return 0;
}