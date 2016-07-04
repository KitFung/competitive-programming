#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;

LL convertbase(LL origin, LL base) {
    LL result = 0;
    LL t = origin;
    LL thisv;
    int d10 = 1;
    while (t > 0) {

        thisv = t % base;
        if (thisv > 9) return -1;
        result += thisv * d10;

        t /= base;
        d10 *= 10;
    }

    return result;
}


int main() {
    // freopen("input.txt", "r", stdin);
    LL y, l, tmp;
    LL base;
    while (scanf("%lld%lld", &y, &l) != EOF) {
        base = 10;
        for (LL i = 10; i <= 1000000; ++i) {
            tmp = convertbase(y, i);
            if (tmp != -1 && tmp >= l) {
                base = i;
            }
        }

        for (LL a0 = 0; a0 < 10; ++a0) {
            for (LL a1 = 0; a1 < 10; ++a1) {
                for (LL a2 = 0; a2 < 10; ++a2) {
                    for (LL a3 = 0; a3 < 10; ++a3) {
                        if (a3 * 1000 + a2 * 100 + a1 * 10 + a0 < l) continue;

                        LL head = 11, tail = 1e18 + 10, m;
                        while (head < tail) {
                            m = (head + tail) >> 1;
                            double d = m;

                            if (a3 * d * d * d + a2 * d * d + a1 * d + a0 > 1e18) {
                                tail = m - 1;
                            }
                            else if (a3*m*m*m + a2*m*m + a1*m + a0 > y) {
                                tail = m - 1;
                            }
                            else
                                head = m + 1;

                            if (a3*m*m*m + a2*m*m + a1*m + a0 == y) {
                                head = m;
                                break;
                            }
                        }
                        m = head;
                        if (a3*m*m*m + a2*m*m + a1*m + a0 == y) {
                            base = max(base, m);
                        }
                    }
                }
            }
        }
        printf("%lld\n", base);
    }
    return 0;
}
