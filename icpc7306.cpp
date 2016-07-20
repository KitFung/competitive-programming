#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

const LL MAXN = 1e14 + 5;
const int MAXF = 1e7 + 5;
const LL MODV = 1000000007;

vector< pair<LL, int> > degrees;
vector<LL> ans;
bool isprime[MAXF];

void add_primes(int a) {
  for(double i = (double)a*a; i < MAXN; i*=a)
    degrees.push_back( make_pair(i, a) );
}

void build_ans() {
  memset(isprime, true, sizeof(isprime));

  isprime[0] = isprime[1] = false;
  degrees.push_back( make_pair(1, 1) );
  for(LL i = 4; i < MAXF; i += 2) {
    isprime[i] = false;
  }
  add_primes(2);
  for(int i = 3; i < MAXF; i += 2)
    if(isprime[i]) {
      add_primes(i);
      for(LL j = i*2; j < MAXF; j += i) {
        isprime[j] = false;
      }
    }

  sort(degrees.begin(), degrees.end());
  ans.push_back(1);
  for(int i = 1; i < degrees.size(); ++i) {
    ans.push_back( (ans[i-1]*degrees[i].second)%MODV );
  }
}

int main() {
  build_ans();

  int N;
  LL val;
  scanf("%d", &N);
  for(int i = 1; i <= N; ++i) {
    scanf("%lld", &val);
    int head = 0, tail = degrees.size()-1, mid;
    while(head < tail) {
      mid = (head+tail+1) >> 1;

      if(degrees[mid].first > val) {
        tail = mid - 1;
      } else {
        head = mid;
      }
    }
    printf("Case %d: %lld\n", i, ans[head]);
  }
  return 0;
}
