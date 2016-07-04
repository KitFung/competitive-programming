#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct cmpByGain {
  bool operator() (pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
  }
};

struct cmpByGain2 {
  bool operator() (pair<int, int> a, pair<int, int> b) {
    return a.second + a.first > b.second + b.first;
  }
};

int main() {
  int n, oldc, newc;
  while(scanf("%d", &n) != EOF) {

    vector< pair<int, int> > diskG, diskL;
    for(int i = 0; i < n; ++i) {
      scanf("%d%d", &oldc, &newc);
      if(newc > oldc)
        diskG.push_back(make_pair(oldc, newc-oldc));
      else
        diskL.push_back(make_pair(oldc, newc-oldc));
    }

    sort(diskG.begin(), diskG.end(), cmpByGain());
    sort(diskL.begin(), diskL.end(), cmpByGain2());

    long long capc = 0;
    long long requirenew = 0;

    for(int i = 0; i < diskG.size(); ++i) {
      if(diskG[i].first > capc) {
        requirenew += diskG[i].first - capc;
        capc = diskG[i].first + diskG[i].second;
      } else {
        capc += diskG[i].second;
      }
    }

    for(int i = 0; i < diskL.size(); ++i) {
      if(diskL[i].first > capc) {
        requirenew += diskL[i].first - capc;
        capc = diskL[i].first + diskL[i].second;
      } else {
        capc += diskL[i].second;
      }
    }

    printf("%lld\n", requirenew);
  }
  return 0;
}
