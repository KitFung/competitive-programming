#include <cstdio>

typedef long long LL;


int main() {
    // freopen("input.txt", "r", stdin);

    LL a, b;
    int counter = 1;
    while(scanf("%lld%lld", &a, &b) != EOF && (a && b)) {
        LL ta = a * (a-1);
        LL tb = b * (b-1);

        printf("Case %d: %lld\n",counter++, (ta*tb)/4);
    }

    return 0;
}