#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-8;

int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

double mySqrt(double x) {
    return sqrt(max((double)0, x));
}


struct Point {
    double x, y;
    Point() {}
    Point(double a, double b): x(a), y(b) {}
    Point& operator = (Point p) {
        x = p.x;
        y = p.y;
        return *this;
    }
};
typedef Point Vector;
Vector operator + (Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, double p) { return Vector(a.x * p, a.y * p); }
Vector operator / (Vector a, double p) { return Vector(a.x / p, a.y / p); }

double dot(Vector a, Vector b) { return a.x*b.x + a.y*b.y; }
double cross(Vector a, Vector b) { return a.x*b.y - a.y*b.x; }

struct Line {
    Point p;
    Vector v;
    Line(Point p, Vector v) : p(p), v(v) {}
    Point getPoint(double t) {
        return Point(p.x + t*v.x, p.y + t*v.y);
    }
};

struct Circle {
    Point c;
    double r;
    Circle(Point c, double r) : c(c), r(r) {}
};

double dists(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
// Here b is the the b in question, is the line AB intersect circle
// assume ab is 1
// t*(ABx^2 + ABy^2) - (ABx*CAx + ABy*CAy) = 0
// let ABx = a, ABy = c, CAx = b, CAy = d;
int getLineCircleIntersection(Line L, Circle C, Point& Q) { //返回t较小的那个点
    double a = L.v.x;
    double b = L.p.x - C.c.x;
    double c = L.v.y;
    double d = L.p.y - C.c.y;

    double e = a*a + c*c;
    double t = (-1 * (a*b + c*d)) / e;
    Point p = L.getPoint(t);

    double cp = dists(p, C.c);
    if (cp > C.r) return 0;
    double qp = sqrt(C.r*C.r - cp*cp);

    double ap = dists(p, L.p);

    double ratio = (ap - qp) / ap;
    Q = L.getPoint(t*ratio);

    return true;
}

// A in Line L
bool onRay(Point A, Line L) {
    Vector LA = A - L.p;
    // sin 0 = 0, cos 0 = 1 
    return dcmp(cross(LA, L.v)) == 0 && dcmp(dot(LA, L.v)) > 0;;
}


// A in BC
bool onSegment(Point A, Point B, Point C) {
    // sin 180 = 0, cos 180 = -1 
    return dcmp(cross(B - A, C - A)) == 0 && dcmp(dot(B - C, C - A)) < 0;
}


// the mid point between A and D
Point mirrorVec(Point A, Line L) {
    // |lv| |AO| cosx / |lv| |lv| 1 = OC / |lv|
    // (ga)^2 + (gb)^2 = (gc)^2, ratio in length change can be used in ratio in x, y change
    double ratioOC2OD = dot(L.v, A - L.p)/dot(L.v, L.v);
    return L.p + L.v * ratioOC2OD;
}

Point mirrorPoint(Point A, Line L) {
    Vector D = mirrorVec(A, L);
    return D + (D - A);
}


Point O, A, B, Q;
Vector V;
double radius;

bool canTouch() {
    Circle C(O, radius);
    Line LA(A, V);
    if (getLineCircleIntersection(LA, C, Q)) {
        if (onSegment(B, A, Q)) return true;

        Line CQ(O, Q - C.c);
        Point mA = mirrorPoint(A, CQ);

        Line QB(Q, B - Q);
        if(onRay(mA, QB)) {
            return true;
        }
    }
    else {
        if (onRay(B, LA)) return true;
    }
    return false;
}

int main() {
    // freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);
    for (int tcase = 1; tcase <= T; ++tcase) {
        scanf("%lf%lf%lf", &O.x, &O.y, &radius);
        scanf("%lf%lf%lf%lf", &A.x, &A.y, &V.x, &V.y);
        scanf("%lf%lf", &B.x, &B.y);
        
        if (!canTouch()) {
         printf("Case #%d: No\n", tcase);
        }
        else {
         printf("Case #%d: Yes\n", tcase);
        }
    }

    return 0;
}


