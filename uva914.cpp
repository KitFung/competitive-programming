#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;

bool isprime[MAXN];
vector<int> primes;
map<int, int> counter;

void slave_prime() {
    memset(isprime, true, sizeof(isprime));
    isprime[0] = isprime[1] = false;
    for(int i = 4; i < MAXN; i+=2)
        isprime[i] = false;

    int limit = sqrt(MAXN) + 1;
    for(int i = 3; i < limit; i+=2)
        if(isprime[i]) {
            int a = (MAXN - 1)/i;
            int b = a * i;
            for(; a >= i; a--, b-=i)
                isprime[b] = false;
        }

    primes.push_back(2);
    for(int i = 3; i < MAXN; i+=2)
        if(isprime[i]) {
            primes.push_back(i);
        }
}

int cal_diff(int upper, int end) {
    int upper_idx = lower_bound(primes.begin(), primes.end(), upper) - primes.begin();
    if(primes[upper_idx] != upper) upper_idx--;

    int lower_idx = lower_bound(primes.begin(), primes.end(), end) - primes.begin();

    if( (upper_idx-lower_idx) < 1) return -1;
    counter.clear();

    for(int i = lower_idx; i < upper_idx; ++i) {
        int diff = primes[i+1] - primes[i];
        if(counter.find(diff) == counter.end())
            counter[diff] = 1;
        else
            counter[diff]++;
    }

    int maxc = 0, maxvalue = 0;
    int nmax = 0;
    for(map<int, int>::iterator i=counter.begin(); i != counter.end(); ++i) {
        if(maxvalue < (*i).second) {
            maxc = (*i).first;
            maxvalue = (*i).second;
            nmax = 1;
        } else if(maxvalue == (*i).second) {
            nmax++;
        }
    }

    if(nmax != 1) return -1;
    return maxc;
}


int main() {
    slave_prime();

    int n, upper, lower;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &lower, &upper);
        int r = cal_diff(upper, lower);
        if(r == -1) {
            printf("No jumping champion\n");
        } else {
            printf("The jumping champion is %d\n", r);
        }
    }
    return 0;
}