#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double get_bit(int year) {
    double bit = 4;
    year -= 1960;
    while(year >= 10) {
        bit *= 2;
        year -= 10;
    }
    return bit;
}

vector<double> fac;


int main() {
    int year;
    while(scanf("%d", &year) != EOF && year != 0) {
        int bit = get_bit(year);

        int k = 1;
        double a = 0;

        while(a < bit) {
            a += log(k*1.0)/log(2.0);
            k++;
        }
        printf("%d\n", k - 2);
    }
    return 0;
}