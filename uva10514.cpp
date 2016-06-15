#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

const int INFI =  1 << 30;
const int MAXN = 110;
const int MAXNODEINISLAND = 15;
const int MAXNODE = 50;

typedef struct pt
{
    double x, y;
    pt() {}
    pt(double _x, double _y): x(_x), y(_y) {}
} Point;

typedef Point PointGroup[MAXN];

PointGroup riverBandA, riverBandB;
PointGroup islands[MAXNODEINISLAND];
int nodeinislands[MAXNODEINISLAND];

double cost[MAXNODE];
bool visited[MAXNODE];
double adj[MAXNODE][MAXNODE];


double distance_p(const Point &a, const Point &b) {
    return hypot((a.x-b.x), (a.y-b.y));
}

// ab . ac
double dot(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x)*(c.x - a.x) + (b.y - a.y)*(c.y - a.y);
}

// Point c to line a, b
double distance_abc(const Point &c, const Point &a, const Point &b) {
    double dot1 = dot(a, b, c);
    double dot2 = dot(b, a, c);
    double l1 = distance_p(a, c);

    if(dot1 > 0 && dot2 > 0) {
      double l = distance_p(a, b);
      double cosv = dot1/l1/l;
      // sqrt(1 - cosv*cosv) == sin(x)
      // distance/l1 = sin(x)
      return l1 * sqrt(1 - cosv*cosv);
    } else {
      return min(l1, distance_p(b, c));
    }
}

void read_input(int r1, int r2, int n) {
    for (int i = 0; i < r1; ++i) {
        scanf("%lf%lf", &riverBandA[i].x, &riverBandA[i].y);
    }

    for (int i = 0; i < r2; ++i) {
        scanf("%lf%lf", &riverBandB[i].x, &riverBandB[i].y);
    }

    for (int i = 0; i < n; ++i) {
        scanf("%d", &nodeinislands[i]);

        for(int j = 0; j < nodeinislands[i]; ++j) {
            scanf("%lf%lf", &islands[i][j].x, &islands[i][j].y);
        }
    }
}

double distance_gp(PointGroup &a, int lena, PointGroup &b, int lenb, bool isbina, bool isbinb) {
    double minV = INFI;

    for (int i = 0; i < lena; ++i) {
        for (int j = 0; j < lenb; ++j) {
            if(isbinb && lenb - 1 == j) break;
            minV = min(minV, distance_abc(a[i], b[j], b[(j+1)%lenb]));
        }
    }

    for (int i = 0; i < lenb ; ++i) {
        for (int j = 0; j < lena; ++j) {
            if(isbina && lena - 1 == j) break;
            minV = min(minV, distance_abc(b[i], a[j], a[(j+1)%lena]));
        }
    }

    return minV;
}

void build_network(int r1, int r2, int n) {

    adj[0][1] = adj[1][0] = distance_gp(riverBandA, r1, riverBandB, r2, true, true);

    for (int i = 0; i < n; ++i) {
        adj[0][i + 2] = adj[i + 2][0] = distance_gp(riverBandA, r1, islands[i], nodeinislands[i], true, false);
        adj[1][i + 2] = adj[i + 2][1] = distance_gp(riverBandB, r2, islands[i], nodeinislands[i], true, false);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adj[i + 2][j + 2] = adj[j + 2][i + 2] = distance_gp(islands[i], nodeinislands[i], islands[j], nodeinislands[j], false, false);
        }
    }
}

double shortest_distance(int ncount, int startidx, int endidx) {
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < ncount; ++i)
        cost[i] = INFI;

    cost[startidx] = 0;

    for(int k = 0; k < ncount; ++k) {
        int a = -1;
        double minV = INFI;
        for (int i = 0; i < ncount; ++i) {
            if (!visited[i] && cost[i] < minV) {
                minV = cost[i];
                a = i;
            }
        }

        if (a == -1)
            break;

        visited[a] = true;

        for (int i = 0; i < ncount; ++i) {
            if (a == i || visited[i])
                continue;
            if(cost[a] + adj[a][i] < cost[i])
                cost[i] = cost[a] + adj[a][i];
        }
    }

    return cost[endidx];
}


int main() {

    int nscen;
    int r1, r2, n;

    scanf("%d", &nscen);

    for (int i = 0; i < nscen; ++i) {
        scanf("%d%d%d", &r1, &r2, &n);
        read_input(r1, r2, n);
        build_network(r1, r2, n);
        double s_dist = shortest_distance(n + 2, 0, 1);
        printf("%.3lf\n", s_dist);
    }

    return 0;
}
