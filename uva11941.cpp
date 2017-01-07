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

int build_tree(int k, int lx, int ly, int rx, int ry) {

  if(lx == rx && ly == ry)
    return node[k] = (1 << g[lx][ly]);

  int mx = (lx + rx) >> 1, my = (ly + ry) >> 1;
  int v = 0; // v mean which color this node have. It use 1 bit to represent each color
  v |= build_tree(LeftTop, lx, ly, mx, my);
  v |= build_tree(RightTop, mx+1, ly, rx, my);
  v |= build_tree(LeftBot, lx, my+1, mx, ry);
  v |= build_tree(RightBot, mx+1, my+1, rx, ry);

  return node[k] = v;
}

void dfs(int k) {
  if(node[k] == 0b11) {
    if(k > 1) printf("*");
    dfs(LeftTop);
    dfs(RightTop);
    dfs(LeftBot);
    dfs(RightBot);
  } else if(node[k] == 0b01) {
    printf("0");
  } else {
    printf("1");
  }
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
  // freopen("input.txt", "r", stdin);
  int ncase, n;
  scanf("%d\n", &ncase);

  while (ncase--) {
    gets(line);
    stringstream sin(line);
    string token;
    sin >> n;
    if (!powerof2(n)) {
      printf("Size is invalid\n");
      continue;
    }

    memset(g, 0, sizeof(g));

    int sx, sy, ex, ey;
    while (sin >> token) {
      sscanf(token.c_str(), "(%d,%d)", &sx, &sy);
      if (sin >> token) {
        sscanf(token.c_str(), "(%d,%d)", &ex, &ey);
        --sx, --sy, --ex, --ey; // start from 0
        for (int i = sx; i <= ex; ++i)
          for (int j = sy; j <= ey; ++j)
            g[i][j] = 1;
      }
    }
    build_tree(1, 0, 0, n-1, n-1);
    dfs(1);
    printf("\n");
  }
  return 0;
}
