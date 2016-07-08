#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> bs;
vector<int> rbs;
vector< pair<int, int> > ininder;

struct Node {
  bool covered;
} node [1000000];

inline int LC(int i) { return (i << 1); }
inline int RC(int i) { return (i << 1) + 1; }
bool sf;

void build() {
  memset(node, 0, sizeof(node));
}

void pushDown(int idx) {
  if(node[idx].covered) {
    node[LC(idx)].covered = node[RC(idx)].covered = node[idx].covered;
  }
}

void update_query(int L, int R, int idx, int tL, int tR) {
  if(tL <= L && R <= tR || node[idx].covered) {
    if(!node[idx].covered) {
      node[idx].covered = true;
      sf = true;
    }
    return;
  }

  pushDown(idx);
  int have_space = false;
  int M = (L + R) >> 1;
  if (tL <= M) update_query(L, M, LC(idx), tL, tR);
  if (tR > M) update_query(M+1, R, RC(idx), tL, tR);

  node[idx].covered = node[LC(idx)].covered && node[RC(idx)].covered;
}

void build_bs() {
  sort( bs.begin(), bs.end() );
  bs.erase( unique( bs.begin(), bs.end() ), bs.end() );
  int bn = bs.size();
  for(int i = 0; i < bn - 1; ++i) {
    rbs.push_back(bs[i]);
    if(bs[i+1] - bs[i] > 1)
      rbs.push_back(bs[i]+1);
  }
  rbs.push_back(bs[bn - 1]);
}

void solve(int n) {
  ininder.clear();
  bs.clear();
  rbs.clear();
  build();

  int s, e, countss = 0;
  int low_idx, high_idx;
  for(int i = 0; i < n; ++i) {
    scanf("%d%d", &s, &e);
    ininder.push_back(make_pair(s, e));
    bs.push_back(s);
    bs.push_back(e);
  }
  build_bs();
  int as = rbs.size();
  for(int i = n-1; i >= 0; --i) {
    sf = false;
    low_idx = find(rbs.begin(), rbs.end(), ininder[i].first) - rbs.begin();
    high_idx = find(rbs.begin(), rbs.end(), ininder[i].second) - rbs.begin();
    update_query(1, as, 1, low_idx+1, high_idx+1);
    if(sf) countss++;
  }
  printf("%d\n", countss);
}

int main () {
  // freopen("input.txt", "r", stdin);
  int ncase, n;
  scanf("%d", &ncase);
  for(;ncase-- > 0;) {
    scanf("%d", &n);
    solve(n);
  }
  return 0;
}
