#include <cstdio>

int gcd(int a, int b) {
    if(a < b) return gcd(b, a);
    if(b == 0) {
        return a;
    }
    return gcd(b, a%b);
}

int main() {
    int step, mod;
    while(scanf("%d%d", &step, &mod) != EOF) {
        printf("%10d%10d    ", step, mod);
        printf("%s Choice\n\n", gcd(step, mod)==1?"Good":"Bad");
    }
    return 0;
}