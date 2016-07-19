#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


int main() {
  // freopen("input.txt", "r", stdin);
  int ncase, N, L, value;
  int ansA, ansB, ansC;
  int accum = 0;
  int preV = 0;
  vector<int> vec;

  scanf("%d", &ncase);
  for(int i = 1; i <= ncase; ++i) {
    scanf("%d%d", &N, &L);
    for(int v = 0 ; v < N; ++v) {
      scanf("%d", &value);
      vec.push_back(value);
    }
    sort(vec.begin(), vec.end());
    accum = 0;
    ansA = ansB = ansC = 0;
    for(int z = 0; z < vec.size(); ++z) {
      if(ansB + vec[z] > L) break;
      ansA++;
      ansB += vec[z];
      ansC += ansB;
    }
    vec.clear();
    printf("Case %d: %d %d %d\n", i, ansA, ansB, ansC);
  }
  return 0;
}
