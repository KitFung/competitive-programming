#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
//https://uva.onlinejudge.org/external/101/p10171.pdf
const int INFI = 1 << 26;

bool visited[26];
int placeMe[26];
int placeHe[26];
int roadMe[26][26];
int roadHe[26][26];
int meStartPt;
int heStartPt;


void build_my_road() {
  memset(visited, false, sizeof(visited));
  for(int i = 0; i < 26; ++i) placeMe[i] = INFI;
  placeMe[meStartPt] = 0;

  for(int k = 0; k < 26; ++k) {
    int a = -1, minv = INFI;
    for(int i = 0; i < 26; ++i) {
      if(!visited[i] && placeMe[i] < minv) {
        a = i;
        minv = placeMe[i];
      }
    }

    if(a == -1) return;
    visited[a] = true;

    for(int i = 0; i < 26; ++i) {
      if(a == i || visited[i] || roadMe[a][i] == INFI)
        continue;
      if(placeMe[a] + roadMe[a][i] < placeMe[i]) {
        placeMe[i] = placeMe[a] + roadMe[a][i];
      }
    }
  }

}

void build_his_road() {
  memset(visited, false, sizeof(visited));
  for(int i = 0; i < 26; ++i) placeHe[i] = INFI;
  placeHe[heStartPt] = 0;

  for(int k = 0; k < 26; ++k) {
    int a = -1, minv = INFI;
    for(int i = 0; i < 26; ++i) {
      if(!visited[i] && placeHe[i] < minv) {
        a = i;
        minv = placeHe[i];
      }
    }

    if(a == -1) return;
    visited[a] = true;

    for(int i = 0; i < 26; ++i) {
      if(a == i || visited[i] || roadHe[a][i] == INFI)
        continue;
      if(placeHe[a] + roadHe[a][i] < placeHe[i]) {
        placeHe[i] = placeHe[a] + roadHe[a][i];
      }
    }
  }
}

void find_common_place() {
  int minv = INFI, a = -1;
  vector<char> v;
  for(int i = 0; i < 26; ++i) {
    if(placeHe[i] == INFI || placeMe[i] == INFI)
      continue;
    if(placeHe[i] + placeMe[i] < minv) {
      minv = placeHe[i] + placeMe[i];
      v.clear();
      v.push_back(i);
    } else if(placeHe[i] + placeMe[i] == minv) {
      v.push_back(i);
    }
  }
  if(v.size() == 0)
    printf("You will never meet.\n");
  else{
    printf("%d", minv);
    for(int i = 0; i < v.size(); ++i)
      printf(" %c", (v[i] + 'A'));
    printf("\n");
  }
}

void read_input(int n) {
  for(int i = 0; i < 26; ++i)
    for(int j = 0; j < 26; ++j) {
      roadMe[i][j] = roadHe[i][j] = INFI;
    }

  int cost;
  char young[2], bidirect[2], from[2], to[2];
  for(int i = 0; i < n; ++i) {
    scanf("%s%s%s%s%d", young, bidirect, from, to, &cost);
    int f = from[0] - 'A';
    int t = to[0] - 'A';

    if(young[0] == 'Y') {
      roadMe[f][t] = min(cost, roadMe[f][t]);
      if(bidirect[0] == 'B') {
        roadMe[t][f] = min(cost, roadMe[t][f]);
      }
    } else {
      roadHe[f][t] = min(cost, roadHe[f][t]);
      if(bidirect[0] == 'B') {
        roadHe[t][f] = min(cost, roadHe[t][f]);
      }
    }
  }
  scanf("%s%s", from, to);
  meStartPt = from[0] - 'A';
  heStartPt = to[0] - 'A';
}

int main() {

  int n;
  while(scanf("%d", &n) != EOF && n) {
    read_input(n);
    build_my_road();
    build_his_road();
    find_common_place();
  }
  return 0;
}
