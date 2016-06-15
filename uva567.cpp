#include <cstdio>
#include <cstring>
#include <cmath>


const int INFI = 1 << 20;

bool visited[25];
int country[25][25];

void floyd() {
  for(int k = 1; k <= 20; ++k)
    for(int i = 1; i <= 20; ++i)
      for(int j = 1; j <= 20; ++j)
        if(i != j && country[i][k] + country[k][j] < country[i][j])
          country[i][j] = country[i][k] + country[k][j];
}

int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  int n, c, testn, from, to;
  int count = 1;

  while(true) {
    for(int i = 0; i <= 20; ++i)
      for(int j = 0; j <= 20; ++j)
        country[i][j] = INFI;

    for(int i = 1; i <= 19; ++i) {
      if(scanf("%d", &n) == EOF) return 0;
      for(int j = 0; j < n; ++j) {
        scanf("%d", &c);
        country[c][i] = country[i][c] = 1;
      }
    }
    floyd();
    scanf("%d", &testn);

    printf("Test Set #%d\n", count++);
    for(int i = 0; i < testn; ++i) {
      scanf("%d%d", &from, &to);
      printf("%2d to %2d: %d\n", from, to, country[from][to]);
    }
    printf("\n");

  }
}
