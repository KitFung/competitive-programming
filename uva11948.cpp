#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;

#define LeftTop k<<2
#define RightTop (k<<2)+1
#define LeftBot (k<<2)+2
#define RightBot (k<<2)+3

const int MAXN = 1024;
const int MAXM = 32767;

char g[MAXN][MAXN];
char node[MAXN * MAXN];
char line[MAXM];
int idx;

void build_tree(int k, int lx, int ly, int rx, int ry) {

  char type = line[idx++];

  int mx = (lx + rx) >> 1, my = (ly + ry) >> 1;
  if(type == '*') { // have different type below, then it will not be a end node
    build_tree(LeftTop, lx, ly, mx, my);
    build_tree(RightTop, mx+1, ly, rx, my);
    build_tree(LeftBot, lx, my+1, mx, ry);
    build_tree(RightBot, mx+1, my+1, rx, ry);
  } else {
    for(int i = lx; i <= rx; ++i)
      for(int j = ly; j <= ry; ++j)
        g[i][j] = type;
  }
}

void solve(int n) {
  bool first = true;

  for(int y = 0; y < n; ++y)
    for(int x = 0; x < n; ++x) {
      if(g[x][y] == '1') {
        int l = x, r = x;
        while(r < n && g[r][y] == '1') ++r;

        if(!first) {
          printf(",");
        } else {
          first = false;
        }

        if(r == l+1)
          printf("(%d,%d)", x+1, y+1);
        else
          printf("(%d-%d,%d)", l+1, r, y+1);

        x = r;
      }
    }

  printf("\n");
}

bool powerof2(int n) {
  if (n <= 1)
    return false;
  while (n) {
    if ((n & 1) && n != 1)
      return false;
    n >>= 1;
  }
  return true;
}

int main() {
  int ncase, n;
  scanf("%d\n", &ncase);

  while (ncase--) {
    scanf("%d%s", &n, line);

    if (!powerof2(n)) {
      printf("Invalid length\n");
      continue;
    }

    idx = 0;

    build_tree(1, 0, 0, n-1, n-1);
    solve(n);
  }
  return 0;
}
