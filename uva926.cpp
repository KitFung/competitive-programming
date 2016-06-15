#include <cstdio>
#include <cstring>

long long street[100][100];

int main () {

  int C, N, W;
  int startX, startY;
  int endX, endY;
  int x, y;
  char dir;
  int i2, j2;

  scanf("%d\n", &C);

  for(int i = 0; i < C; ++i) {
    memset(street, 0, sizeof(street));
    scanf("%d\n", &N);
    scanf("%d%d\n", &startX, &startY);
    scanf("%d%d\n", &endX, &endY);

    scanf("%d\n", &W);
    for(int j = 0; j < W; ++j) {
      scanf("%d %d %c\n", &x, &y, &dir);
      x*=2;
      y*=2;
      if(dir == 'N')
        y++;
      else if(dir == 'E')
        x++;
      else if(dir == 'S')
        y--;
      else
        x--;
      street[x][y] = -1;
    }

    street[startX*2][startY*2] = 1;
    for(int i = startY; i <= endY; ++i) {
      for(int j = startX; j <= endX; ++j) {
        i2 = i * 2;
        j2 = j * 2;
        if(street[j2+1][i2] != -1) {
          street[j2+2][i2] += street[j2][i2];
        }
        if(street[j2][i2+1] != -1) {
          street[j2][i2+2] += street[j2][i2];
        }
      }
    }

    printf("%lld\n", street[endX*2][endY*2]);
  }

  return 0;
}
