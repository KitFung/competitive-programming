#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int n, a;
int sum, limit;
int v[110];
int v2[110];

bool validate(int t) {
  memcpy (&v2, &v, sizeof(v));

  int t2 = t;
  for(int i = 0; i < n; ++i) {
    while(v2[i] > 0) {
      if(v2[i]-t2 < 0) return false;
      v2[i] -= t2--;
      if(t2 == 0) break;
    }
    if(t2 == 0) break;
  }

  if(t2 != 0) return false;
  t2 = t;
  for(int i = n - 1; i >= 0; --i) {
    while(v2[i] > 0) {
      if(v2[i]-t2 < 0) return false;
      v2[i] -= t2--;
      if(t2 == 0) break;
    }
    if(t2 == 0) break;
  }
  return t2 == 0;
}

int main() {

  while(scanf("%d", &n) != EOF) {
    sum = 0;

    for(int i = 0; i < n; ++i) {
      scanf("%d", &v[i]);
      sum += v[i];
    }

    limit = min(v[0], v[n - 1]);

    if(sum%2 == 1) {
      printf("no quotation\n");
    } else {
      bool found = false;
      for(int i = limit; i > 0; --i) {
        if(validate(i)) {
          if(i == 1 && sum != 2) break;
          found = true;
          printf("%d\n", i);
          break;
        }
      }
      if(!found) printf("no quotation\n");
    }
  }
  return 0;
}
