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

typedef long long ll;

const int MAXM = 20000000;

ll arr[MAXM];
char g[200][200];
int node_color[MAXM];

int dfs(int k, int lx, int ly, int rx, int ry) {
  if(lx == rx && ly == ry) {
    int mv = g[ry][lx] == '0'?0:1;
    return node_color[k] = 1 << mv;
  }

  int mx = (lx + rx) >> 1, my = (ly + ry) >> 1;

  node_color[k] = 0;
  node_color[k] |= dfs(LeftTop, lx, ly, mx, my);
  node_color[k] |= dfs(RightTop, mx+1, ly, rx, my);
  node_color[k] |= dfs(LeftBot, lx, my+1, mx, ry);
  node_color[k] |= dfs(RightBot, mx+1, my+1, rx, ry);

  return node_color[k];
}

int aidx;
void pickuptree(int k, ll num, ll base) {
  if(node_color[k] == 0b01 || node_color[k] == 0b10) {
    if(node_color[k] == 0b10) arr[aidx++] = num;
    return;
  }

  ll tbase = base*5;
  pickuptree(LeftTop, num + base, tbase);
  pickuptree(RightTop, num + base*2, tbase);
  pickuptree(LeftBot, num + base*3, tbase);
  pickuptree(RightBot, num + base*4, tbase);
}

void p2g(int k, int lx, int ly, int rx, int ry, ll num) {

  int mx = (lx + rx) >> 1, my = (ly + ry) >> 1;
  if(num == 0) {
    node_color[k] = 2;
    for(int i = lx; i <= rx; ++i)
      for(int j = ly; j <= ry; ++j)
        g[j][i] = '*';

    return;
  }

  ll v = num%5;
  num /= 5;
  if(v == 1) {
    p2g(LeftTop, lx, ly, mx, my, num);
  } else if(v == 2) {
    p2g(RightTop, mx+1, ly, rx, my, num);
  } else if(v == 3) {
    p2g(LeftBot, lx, my+1, mx, ry, num);
  } else {
    p2g(RightBot, mx+1, my+1, rx, ry, num);
  }

}

void solve_g2p(int n) {
  aidx = 0;
  for(int i = 0; i < n; ++i)
    scanf("%s", &g[i]);

  // memset(node_color, 0, sizeof(node_color));
  dfs(1, 0, 0, n-1, n-1);
  pickuptree(1, 0, 1);
  sort(arr, arr+aidx);
  if(aidx) {
    for(int i = 0; i < aidx; ++i) {
      if(i%12) printf(" ");
      printf("%lld", arr[i]);
      if((i+1)%12 == 0)
        printf("\n");
    }
    if(aidx%12)
      printf("\n");
  }

  printf("Total number of black nodes = %d\n", aidx);

}

void solve_p2g(int n) {
  int idx = 0;
  while (scanf("%lld", &arr[idx]) != EOF && arr[idx] >= 0) idx++;

  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      g[i][j] = '.';

  for(int i = 0; i < idx; ++i)
    p2g(1, 0, 0, n-1, n-1, arr[i]);

  for(int i = 0; i < n; ++i) {
    g[i][n] = 0;
    printf("%s\n", g[i]);
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  int n, lastn = 0;
  int ncase = 0;
  while(scanf("%d\n", &n) != EOF && n) {
    if(lastn != 0) printf("\n");

    printf("Image %d\n", ++ncase);
    if(n > 0) {
      lastn = 1;
      solve_g2p(n);
    } else {
      lastn = -1;
      solve_p2g(-1*n);
    }

  }
  return 0;
}
