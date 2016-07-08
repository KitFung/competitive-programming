#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define leftidx (idx<<1)
#define rightidx (idx<<1)|1
// http://blog.csdn.net/scnu_jiechao/article/details/19584715

const int MAXN = 110;

double y[MAXN << 1];

struct Scanline {
  double x, y1, y2;
  bool is_left;

  bool operator < (const Scanline &b) const {
    return x < b.x;
  }
} scanline[MAXN << 1];

struct Node {
  int cover;
  int left, right;
  double len;
} node[MAXN << 3];

int idxOf(double x, int n) {
  return lower_bound(y, y+n, x) - y;
}

void t_build(int idx, int L, int R) {
  node[idx].left = L;
  node[idx].right = R;
  node[idx].len = 0;
  node[idx].cover = 0;
  if(L+1 == R) return;
  int M = (L + R) >> 1;
  t_build(leftidx, L, M);
  t_build(rightidx, M, R);
}

void t_maintain(int idx) {
  if(node[idx].cover > 0) {
      node[idx].len = y[node[idx].right] - y[node[idx].left];
  }
  else if(node[idx].left + 1 == node[idx].right) { // avoid out of bound
      node[idx].len = 0;
  }
  else {
      node[idx].len = node[leftidx].len + node[rightidx].len;
  }
}

void t_updateOne(int idx, int tL, int tR) {
  if(node[idx].left >= tL && node[idx].right <= tR) {
    node[idx].cover++;
    t_maintain(idx);
    return;
  }
  int M = (node[idx].left + node[idx].right) >> 1;
  if(tL < M) t_updateOne(leftidx, tL, tR);
  if(tR > M) t_updateOne(rightidx, tL, tR);
  t_maintain(idx);
}

void t_deleteOne(int idx, int tL, int tR) {
  if(node[idx].left >= tL && node[idx].right <= tR) {
    node[idx].cover--;
    t_maintain(idx);
    return;
  }
  int M = (node[idx].left + node[idx].right) >> 1;
  if(tL < M) t_deleteOne(leftidx, tL, tR);
  if(tR > M) t_deleteOne(rightidx, tL, tR);
  t_maintain(idx);
}

int main() {
  // freopen("input.txt", "r", stdin);
  int n;
  int ncase = 0;
  double x1, y1, x2, y2;
  while(scanf("%d", &n) != EOF && n) {
    for(int idx = 0; idx < n; ++idx) {
      scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
      scanline[leftidx].x = x1;
      scanline[leftidx].y1 = y1;
      scanline[leftidx].y2 = y2;
      scanline[leftidx].is_left = true;
      y[leftidx] = y1;
      scanline[rightidx].x = x2;
      scanline[rightidx].y1 = y1;
      scanline[rightidx].y2 = y2;
      scanline[rightidx].is_left = false;
      y[rightidx] = y2;
    }

    sort(y, y+2*n);
    int count = unique(y, y+2*n) - y;
    sort(scanline, scanline+2*n);
    t_build(1, 0, count-1);
    double area = 0;

    for(int i = 0; i < 2*n-1; ++i) {
      if(scanline[i].is_left) {
        t_updateOne(1, idxOf(scanline[i].y1, count), idxOf(scanline[i].y2, count));
      } else {
        t_deleteOne(1, idxOf(scanline[i].y1, count), idxOf(scanline[i].y2, count));
      }
      area += (scanline[i+1].x - scanline[i].x) * node[1].len;
    }

    printf("Test case #%d\n", ++ncase);
    printf("Total explored area: %.2f\n\n", area);
  }
  return 0;
}
