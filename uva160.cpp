#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> primes;

void sieve_prime() {
  const int N = 200;
  bool is_prime[N];
  memset(is_prime, true, sizeof(is_prime));

  for(int i = 4; i < N; i += 2)
    is_prime[i] = false;

  int limit = sqrt(N) + 1;
  for(int i = 3; i < limit; i += 2)
    if(is_prime[i]) {
      for(int j = i + i; j < N; j += i)
        is_prime[j] = false;
    }

  for(int i = 2; i < N; ++i)
    if(is_prime[i])
      primes.push_back(i);
}

void solve(int n) {
  printf("%3d! =", n);
  for(int i = 0; i < primes.size(); ++i) {
    if(n < primes[i]) break;
    int count = 0;
    for(int j = 2; j <= n; ++j) {
      int cpy = j;
      while(cpy % primes[i] == 0) {
        count++;
        cpy /= primes[i];
      }
    }
    if(i != 0 && i%15 == 0)
      printf("\n      ");
    printf("%3d", count);
  }
  printf("\n");
}

int main() {
  sieve_prime();
  int n;
  while(scanf("%d", &n) != EOF && n) {
    solve(n);
  }
  return 0;
}
