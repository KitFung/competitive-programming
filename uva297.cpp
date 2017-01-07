#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

#define LeftTop k<<2
#define RightTop (k<<2)+1
#define LeftBot (k<<2)+2
#define RightBot (k<<2)+3

const int MAXN = 35;
const int MAGIC = 32;

int g[MAXN][MAXN];
char buf[1000000];
int res;
int bidx;

void put_on_tree(int k, int lx, int ly, int rx, int ry) {
  // printf("%d| %d %d %d %d\n", k, lx, ly, rx, ry);
  int mx = (lx + rx) >> 1, my = (ly + ry) >> 1;
  if(buf[++bidx] == 'p') {
    put_on_tree(LeftTop, lx, ly, mx, my);
    put_on_tree(RightTop, mx+1, ly, rx, my);
    put_on_tree(LeftBot, lx, my+1, mx, ry);
    put_on_tree(RightBot, mx+1, my+1, rx, ry);
  } else if(buf[bidx] == 'f')
    for(int i = lx; i <= rx; ++i)
      for(int j = ly; j <= ry; ++j)
        if(g[j][i] == 0) {
          res++;
          g[j][i] = 1;
        }

}

void solve() {
  memset(g, 0, sizeof(g));
  res = 0;
  bidx = -1;

  scanf("%s", buf);
  put_on_tree(1, 0, 0, MAGIC-1, MAGIC-1);

  bidx = -1;
  scanf("%s", buf);
  put_on_tree(1, 0, 0, MAGIC-1, MAGIC-1);
  printf("There are %d black pixels.\n", res);
}

int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  int n;
  scanf("%d", &n);
  while(n--) {
    solve();
  }
  return 0;
}
