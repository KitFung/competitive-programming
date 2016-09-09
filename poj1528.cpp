#include <cstdio>
#include <cmath>


int sumOfFactor(int n) {
    if(n == 1) return 0;

    int limit = sqrt(n);
    int sum = 0;
    // printf("%d\n", n);
    for(int i = 1; i <= limit; ++i) {
        if(n % i == 0) {
            // printf("|%d\n", i);
            sum += i;

            int alt = n/i;
            if(alt != n && alt > i)
                sum += alt;
        }
    }
    // printf("--- %d ---\n", sum);
    return sum;
}

int main() {

    int n;
    printf("PERFECTION OUTPUT\n");
    while(scanf("%d", &n) != EOF && n) {
        int s = 0;
        printf("%5d  ", n);
        int fn = sumOfFactor(n) ;

        if(fn == n) {
            printf("PERFECT\n");
        } else if(fn > n) {
            printf("ABUNDANT\n");
        } else {
            printf("DEFICIENT\n");
        }
    }
    printf("END OF OUTPUT\n");
    return 0;
}