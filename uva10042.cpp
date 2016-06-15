#include <cstdio>
#include <cmath>

int sum_of_digit(int v) {
    int sum = 0;
    while(v > 0) {
        sum += v%10;
        v /= 10;
    }
    return sum;
}

int sum_of_factor(int v) {
    if(v == 0) return 0;
    if(v == 1) return 2;

    int sum = 0;
    int remain = v;

    int limit = sqrt(v) + 1;
    int count = 0;

    while(remain % 2 == 0) {
        remain /= 2;
        sum += 2;
        count++;
    }

    for(int i = 3; i <= limit; i += 2) {
        while(remain % i == 0) {
            remain /= i;
            sum += sum_of_digit(i);
            count++;
        }
    }

    if(count == 1 || (count > 1 && remain != 1)) sum += sum_of_digit(remain);
    if(count == 0) sum += 1 + sum_of_digit(v);
    return sum;
}

int main() {
    int ncase,v;
    scanf("%d", &ncase);

    for(;ncase > 0; --ncase) {
        scanf("%d", &v);
        int vv = v + 1;
        while(sum_of_digit(vv) != sum_of_factor(vv))
            vv++;
        printf("%d\n", vv);
    }

    return 0;
}