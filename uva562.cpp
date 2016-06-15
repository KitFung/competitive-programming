#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

bool visited[50010];
vector<int> coins;
vector<int> allpossible;
vector<int> tmp;

int n, m, v, sumofall;
int newv, curv;
double halfv;

bool isnear(const int a, const int b) {
  return abs(sumofall - 2*a) < abs(sumofall - 2*b);
}

int main() {
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) {
    coins.clear();
    allpossible.clear();
    sumofall = 0;
    memset(visited, false, sizeof(visited));

    scanf("%d", &m);
    for(int j = 0; j < m; ++j) {
      scanf("%d", &v);
      coins.push_back(v);
      sumofall += v;
    }

    halfv = sumofall/2.0;
    visited[sumofall] = true;
    allpossible.push_back(sumofall);
    for(int j = 0; j < m; ++j) {
      tmp.clear();
      curv = coins[j];
      for(int k = 0; k < allpossible.size(); ++k) {
        newv = allpossible[k] - curv;
        if(!visited[newv]) {
          visited[newv] = true;
          tmp.push_back(newv);
        }
      }
      for(int l = 0; l < tmp.size(); ++l) {
        allpossible.push_back(tmp[l]);
      }
    }

    sort(allpossible.begin(), allpossible.end(), isnear);
    printf("%d\n", abs(sumofall - 2*allpossible[0]));
  }
  return 0;
}
