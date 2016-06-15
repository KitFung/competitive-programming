#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const int INFI = 1 << 30;
int caccc[60][60];
vector<int> points;

int dfs(int fidx, int tidx) {
  if(caccc[fidx][tidx] != -1) return caccc[fidx][tidx];
  int length = points[tidx] - points[fidx];
  if(tidx - fidx == 1) return 0;

  int minV = INFI;
  for(int i = fidx + 1; i < tidx; ++i) {
    int v = dfs(fidx, i) + dfs(i, tidx) + length;
    minV = min(minV, v);
  }

  caccc[fidx][tidx] = minV;
  return caccc[fidx][tidx];
}

int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  int length, n, v;
  while(scanf("%d", &length) != EOF && length) {
    memset(caccc, -1, sizeof(caccc));
    points.clear();
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
      scanf("%d", &v);
      points.push_back(v);
    }
    points.push_back(0);
    points.push_back(length);
    sort(points.begin(), points.end());

    printf("The minimum cutting is %d.\n", dfs(0, points.size() - 1) );
  }
  return 0;
}
