#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const int CGPA_R_END = 150;
const int CGPA_R_START = 1;

const int CGPA_END = 400;
const int CGPA_START = 250;


int accum_gpa[401];
int presum[401];
int __cnt;

vector<int> p_alloc(int gs, int gr) {
    vector<int> v;
    int val = 0;
    int prepre = presum[gs - 1];
    int cgpa = gs;
    while (cgpa <= 400) {
        cgpa += gr;
        if (cgpa > 400) cgpa = 401;
        v.push_back(presum[cgpa - 1] - prepre);
        prepre = presum[cgpa - 1];
    }
    return v;
}

int extend_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int gcd= extend_gcd(b, a%b, x, y);
    int t = x;
    x = y;
    y = t - (a / b) * y;
    return gcd;
}

// x = ship range, y = ship start
int loop_solve(int a, int b, int c, int count_slot) {

    int count = 0;

    for (int ship_range = 0; ship_range <= 100; ++ship_range) {
        if ((c - a*ship_range) % b != 0) continue;
        int ship_start = (c - a*ship_range) / b;
        if (ship_start > 0 && ship_start < 100 &&
            ship_range > 0 && ship_range <= 100 &&
            ship_start + ship_range*(count_slot - 1) <= 100)
            ++count;
    }

    return count;
}

int main() {
    int N, P, res;
    char cgpa[5];

    while (scanf("%d%d", &N, &P) != EOF && (N || P)) {
        memset(accum_gpa, 0, sizeof(accum_gpa));
        res = 0;
        __cnt = 0;

        for (int n = 0; n < N; ++n) {
            scanf("%s", cgpa);
            int intV = (cgpa[0] - '0') * 100 +
                (cgpa[2] - '0') * 10 +
                (cgpa[3] - '0');
            ++accum_gpa[intV];
        }
        presum[0] += accum_gpa[0];
        for (int i = 1; i <= 400; ++i)
            presum[i] = presum[i - 1] + accum_gpa[i];

        for (int a = CGPA_START; a < CGPA_END; ++a) {
            vector<int> av;
            int preCount = 0;

            for (int b = CGPA_R_START; b <= CGPA_END - a; ++b) {
                vector<int> bv = p_alloc(a, b);

                if (av == bv) {
                    res += preCount;
                    continue;
                }

                av = bv;
                int am = 0, bm = 0;
                int count_slot = bv.size();
                for (int i = 0; i < count_slot; ++i) {
                    am += i * bv[i];
                    bm += bv[i];
                }

                if (bm == 0) {
                    preCount = 0;
                    continue;
                }

                int thisres = loop_solve(am, bm, P, count_slot);
                res += thisres;

                preCount = thisres;
            }
        }

        printf("%d\n", res);
    }

    return 0;
}