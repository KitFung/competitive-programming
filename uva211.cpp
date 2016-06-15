#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

const int MAXX = 8; // 0 - 7
const int MAXY = 7; // 0 - 6


int dominoes[7][7];
int input[10][10];
int curState[10][10];
bool used[29];
int solutionCount;

void build_dominoes() {
  int cardno = 1;
  for(int i = 0; i <= 6; ++i)
    for(int j = i; j <= 6; ++j)
      dominoes[i][j] = dominoes[j][i] = cardno++;
}

bool validXY(int x, int y) {
  return x >= 0 && x < MAXX
      && y >= 0 && y < MAXY;
}

void print_matrix(int input[][10]) {
  for(int i = 0; i < 7; ++i) {
    for(int j = 0; j < 8; ++j)
      printf("%4d", input[j][i]);
    printf("\n");
  }
  printf("\n");
}

void dfs(int curX, int curY ) {
  if(curX == MAXX - 1 && curY == MAXY - 1 && curState[curX][curY] != -1) {
    print_matrix(curState);
    solutionCount++;
    return;
  }

  int nextX = (curX + 1)%MAXX;
  int nextY = curY + (curX + 1)/MAXX;
  int vc = input[curX][curY];
  int vh = input[curX+1][curY];
  int vv = input[curX][curY+1];

  if(curState[curX][curY] != -1) {
    if(validXY(nextX, nextY))
      dfs(nextX, nextY);
    return;
  } else {
    if(validXY(curX+1, curY)) {
      if(curState[curX+1][curY] == -1) {
        int cardno = dominoes[vc][vh];
        if(!used[cardno]) {
          used[cardno] = true;
          curState[curX][curY] = curState[curX+1][curY] = cardno;
          dfs(nextX, nextY);
          curState[curX][curY] = curState[curX+1][curY] = -1;
          used[cardno] = false;
        }
      }
    }
    if(validXY(curX, curY+1)) {
      if(curState[curX][curY+1] == -1) {
        int cardno = dominoes[vc][vv];
        if(!used[cardno]) {
          used[cardno] = true;
          curState[curX][curY] = curState[curX][curY+1] = cardno;
          dfs(nextX, nextY);
          curState[curX][curY] = curState[curX][curY+1] = -1;
          used[cardno] = false;
        }
      }
    }
  }

}

bool readline(int ylevel) {
  for(int i = 0; i < 8; ++i)
    if(scanf("%d", &input[i][ylevel]) == EOF)
      return false;
  return true;
}


int main() {
  build_dominoes();

  int ncase = 0;
  while(readline(0)) {
    for(int i = 1; i < 7; ++i)
      readline(i);

    ncase++;
    solutionCount = 0;
    memset(curState, -1, sizeof(curState));
    memset(used, false, sizeof(used));

    if(ncase != 1)
      printf("\n\n\n");
    printf("Layout #%d:\n\n", ncase);
    print_matrix(input);

    printf("\nMaps resulting from layout #%d are:\n\n", ncase);
    dfs(0, 0);
    printf("\nThere are %d solution(s) for layout #%d.\n", solutionCount, ncase);
  }

  return 0;
}
