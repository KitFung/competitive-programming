#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int dcmp(double a) {
    if(fabs(a) < eps) return 0;
    return a>0?1:-1;
}

struct Point {
    double x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    Point& operator = (Point P) {
        x = P.x;
        y = P.y;
        return *this;
    }
};

typedef Point Vec;

Vec operator - (Point A, Point B) {return Vec(A.x-B.x, A.y-B.y);};

double dot(Vec a, Vec b) { return a.x*b.x + a.y*b.y; }
double cross(Vec a, Vec b) { return a.x*b.y - a.y*b.x; }


vector<Point> allP;
Point Center;

bool inSemiCircle(Vec OA, Point B) {
    Vec OB = B - Center;
    double c = cross(OA, OB);
    return c >= 0;
}

int countInside(int idx) {
    Vec OA = allP[idx] - Center;

    int count = 0;
    for(int i = 0; i < allP.size(); ++i)
        if(i != idx && inSemiCircle(OA, allP[i]))
            count++;

    return count + 1;
}

double dists(Point A, Point B) {
    return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
}

int main() {
    // freopen("input.txt", "r", stdin);

    int npoints;
    double radius;
    while(scanf("%lf%lf%lf", &Center.x, &Center.y, &radius) != EOF && radius > 0) {
        scanf("%d", &npoints);
        allP.clear();

        for(int i = 0; i <npoints; ++i) {
            Point cur;
            scanf("%lf%lf", &cur.x, &cur.y);

            if(dists(Center, cur) <= radius*radius)
                allP.push_back(cur);
        }

        int maxCount = 0;
        for(int i = 0; i < allP.size(); ++i)
            maxCount = max(maxCount, countInside(i));

        printf("%d\n", maxCount);
    }
    return 0;
}