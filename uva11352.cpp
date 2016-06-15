#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 110;
const int dir = 8;
const int hdx[8] = {-2, -1,  1,  2, 2, 1, -1, -2};
const int hdy[8] = {-1, -2, -2, -1, 1, 2,  2,  1};
const int kdx[8] = {-1,  0,  1, 1, 1, 0, -1, -1};
const int kdy[8] = {-1, -1, -1, 0, 1, 1,  1,  0};

char forest[MAXN][MAXN];
bool visited[MAXN][MAXN];
char curline[MAXN];
int AX, AY, BX, BY;


bool isValidXY(int x, int y, int M, int N) {
  return x >= 0
      && x < N
      && y >= 0
      && y < M;
}

int find_min_path(int M, int N) {
  memset(visited, false, sizeof(visited));

  int newX, newY;
  int cX, cY, cC;
  queue< pair<int, int> > ptQ;
  queue<int> stepCount;

  ptQ.push( make_pair(AX, AY) );
  stepCount.push(0);
  visited[AX][AY] = true;

  while(!ptQ.empty()) {
    cX = ptQ.front().first;
    cY = ptQ.front().second;
    cC = stepCount.front();
    ptQ.pop();
    stepCount.pop();

    if(cX == BX && cY == BY) return cC;

    for (int i = 0; i < dir; ++i) {
      newX = cX + kdx[i];
      newY = cY + kdy[i];
      if(isValidXY(newX, newY, M, N) && !visited[newX][newY] && (forest[newX][newY] != 'Z' || forest[newX][newY] == 'B')) {
        visited[newX][newY] = true;
        ptQ.push(make_pair(newX, newY));
        stepCount.push(cC + 1);
      }
    }
  }

  return -1;
}

void mark_all_invalid_pt(int curX, int curY, int M, int N) {
  int newX, newY;
  for(int i = 0; i < dir; ++i) {
    newX = curX+hdx[i];
    newY = curY+hdy[i];
    if(isValidXY(newX, newY, M, N) && forest[newX][newY] != 'B' && forest[newX][newY] != 'A')
      forest[newX][newY] = 'Z';
  }
}

void read_input(int M, int N) {
  memset(forest, 0, sizeof(forest));

  for(int i = 0; i < M; ++i) {
    scanf("%s\n", curline);
    for(int j = 0; j < N; ++j) {
      if(!(curline[j] == '.' && forest[j][i] == 'Z') ) {
        forest[j][i] = curline[j];
        if(forest[j][i] == 'A') {
          AX = j;
          AY = i;
        } else if(forest[j][i] == 'B') {
          BX = j;
          BY = i;
        } else if(forest[j][i] == 'Z') {
          mark_all_invalid_pt(j, i, M, N);
        }
      }
    }
  }
}

int main() {
  int T, M, N;
  int result;

  scanf("%d", &T);
  for(;T-- > 0;) {
    scanf("%d%d", &M, &N);
    read_input(M, N);
    result = find_min_path(M, N);
    if(result == -1)
      printf("King Peter, you can't go now!\n");
    else
      printf("Minimal possible length of a trip is %d\n", result);
  }

  return 0;
}
