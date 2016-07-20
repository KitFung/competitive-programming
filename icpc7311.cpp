#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
  int N, A, B, C;
  int tA, tB, tC;
  int minV;

  A = B = C = 0;
  scanf("%d", &N);
  for(int i = 0; i < N; ++i) {
    scanf("%d%d%d", &tA, &tB, &tC);
    A += tA;
    B += tB;
    C += tC;
    minV = min(A, min(B, C));
    if(minV < 30) {
      printf("NO\n");
    } else {
      printf("%d\n", minV);
      A -= minV;
      B -= minV;
      C -= minV;
    }
  }
  return 0;
}
