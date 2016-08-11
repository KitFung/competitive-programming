#include <cstdio>

int gcd(int a, int b) {
    if(b > a) return gcd(b, a);
    if(b == 0) return a;
    return gcd(b, a%b);
}

int solve(int ex, int ey, int gcr) {
    if(ex < 1 || ey < 1 || gcd(ex, ey) != gcr) return 0;
    int vl = 0, vr = 0;
    int dx = ey/gcr+1;
    int dy = ex/gcr+1;

    if(ey%dy == 0)
        vl = solve(ex, ey/dy, gcr);
    if(ex%dx == 0)
        vr = solve(ex/dx, ey, gcr);

    return vl+vr+1;
}

int main() {
    // freopen("input.txt", "r", stdin);
    int t, ex, ey;
    scanf("%d", &t);
    for(int nt = 1; nt <= t; ++nt) {

        scanf("%d%d", &ex, &ey);
        int gcr = gcd(ex, ey);
        printf("Case #%d: %d\n", nt, solve(ex, ey, gcr));
    }
    return 0;
}