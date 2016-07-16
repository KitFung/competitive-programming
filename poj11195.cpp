#include <cstdio>
#include <cstring>

const int MAXS = 1025;

int tnode[MAXS][MAXS];
int instruct, S, X, Y, A;
int L, B, R, T;

inline int lowbit(int x) {
  return x & (-x);
}

// 1 to S
void addToTree(int i, int j, int v) {
  i++; j++;
  while(j <= S) {
    int ti = i;
    while(ti <= S) {
      tnode[ti][j] += v;
      ti += lowbit(ti);
    }
    j += lowbit(j);
  }
}

int sumFromTree(int i, int j) {
  i++; j++;
  int sum = 0;
  while(j > 0) {
    int ti = i;
    while(ti > 0) {
      sum += tnode[ti][j];
      ti -= lowbit(ti);
    }
    j -= lowbit(j);
  }
  return sum;
}


int main() {
  // freopen("input.txt", "r", stdin);
  scanf("%d%d", &instruct, &S);
  while(scanf("%d", &instruct) != EOF && instruct != 3) {
    if(instruct == 1) {
      scanf("%d%d%d", &X, &Y, &A);
      addToTree(X, Y, A);
    } else {
      scanf("%d%d%d%d", &L, &B, &R, &T);
      printf("%d\n", (sumFromTree(R, T) + sumFromTree(L-1, B-1) - sumFromTree(R, B-1) - sumFromTree(L-1, T)));
    }
  }
  return 0;
}
