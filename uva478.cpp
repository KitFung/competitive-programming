#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

#define PI 3.14159265

typedef struct pt {
  double x, y;
  pt() {}
  pt(double a, double b): x(a), y(b) {}
} Point;

struct Shape {
  Point lt, rb;
  Point center;
  double radius;
  Point vertices[3];
};

double distance_p(const Point &a, const Point &b) {
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

// ao bo
int cross(const Point &a, const Point &b, const Point &o) {
  double v = (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
  if(v == 0) return 0;
  if(v > 0) return 1;
  if(v < 0) return -1;
}

bool isInsideR(const Shape &s, const Point &a) {
  bool xok = s.lt.x < a.x && s.rb.x > a.x;
  bool yok = s.lt.y > a.y && s.rb.y < a.y;
  return xok && yok;
}

bool isInsideT(const Shape &s, const Point &a) {
  int signA = cross(a, s.vertices[0], s.vertices[1]);
  int signB = cross(a, s.vertices[1], s.vertices[2]);
  int signC = cross(a, s.vertices[2], s.vertices[0]);
  return signA == signB && signB == signC;
}

bool isInsideC(const Shape &s, const Point &a) {
  return distance_p(s.center, a) < s.radius;
}

vector<Shape> v;
vector<char> types;

void read_shape() {
  v.clear();
  types.clear();

  char type[4];
  double a, b, c, d, e, f;

  while(scanf("%s\n", type) != EOF && type[0] != '*')  {
    types.push_back(type[0]);

    if(type[0] == 'r') {
      Shape r;
      scanf("%lf%lf%lf%lf", &r.lt.x, &r.lt.y, &r.rb.x, &r.rb.y);
      v.push_back(r);
    } else if(type[0] == 'c') {
      Shape c;
      scanf("%lf%lf%lf", &c.center.x, &c.center.y, &c.radius);
      v.push_back(c);
    } else if(type[0] == 't') {
      Shape t;
      scanf("%lf%lf%lf%lf%lf%lf", &t.vertices[0].x, &t.vertices[0].y,
                                  &t.vertices[1].x, &t.vertices[1].y,
                                  &t.vertices[2].x, &t.vertices[2].y);
      v.push_back(t);
    }
  }
}


int main() {
  // freopen("input.txt", "r", stdin);
  Point cur;
  bool ans;
  int ptcounter = 1;
  bool isinany;

  read_shape();
  while(scanf("%lf%lf", &cur.x, &cur.y) != EOF && (cur.x != 9999.9 && cur.y != 9999.9)) {

    isinany = false;

    for(int i = 0; i < v.size(); ++i) {
      if(types[i] == 'r') {
        ans = isInsideR(v[i], cur);
      } else if(types[i] == 'c')
        ans = isInsideC(v[i], cur);
      else
        ans = isInsideT(v[i], cur);

      if(ans) {
        printf("Point %d is contained in figure %d\n", ptcounter, i + 1);
        isinany = true;
      }
    }
    if(!isinany)
      printf("Point %d is not contained in any figure\n", ptcounter);
    ptcounter++;
  }

  return 0;
}
