#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned long long LL;


LL ansv(LL endidx) {
    if(endidx % 2 == 0)
        return (1+endidx) * (endidx/2);
    else
        return ((1+endidx)/2) * (endidx);
}

int main() {
    int T;
    scanf("%d", &T);

    for(LL ncase = 1; ncase <= T; ++ncase) {
        LL cur ;
        scanf("%lld", &cur);
        LL endidx = ((sqrt(1.0 + 8.0 * cur) - 1.0)/2.0);

        if(ansv(endidx) > cur)
            endidx--;

        printf("Case #%d: %lld\n", ncase, ansv(endidx));
    }

    return 0;
}
