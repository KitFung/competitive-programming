#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const long long MAXN = 47000;
vector<int> all_primes;
vector<int> primes;
bool isprime[MAXN];

void slave_primes() {
    memset(isprime, true, sizeof(isprime));
    isprime[0] = isprime[1] = false;

    for (int i = 4; i < MAXN; i+=2) {
        isprime[i] = false;
    }
    int limit = sqrt(MAXN) + 1;
    for (int i = 3; i <= limit; i+=2) {
        if (isprime[i]) {
            int count = (MAXN-1) / i;
            int product = count * i;
            for ( ; count >= i; --count, product-=i ) {
                if (isprime[count])
                    isprime[product] = false;
            }
        }
    }

    all_primes.push_back(2);
    for (int i = 3; i < MAXN; i+=2) {
        if (isprime[i]) {
            all_primes.push_back(i);
        }
    }
}

bool is_prime(int value) {
    if(value < MAXN) {
        return isprime[value];
    }
    for(int i = 0; i < all_primes.size() && all_primes[i] < value; ++i) {
        if(value % all_primes[i] == 0) return false;
    }
    return true;
}

void calc(int from, int to) {
    primes.clear();
    for (long long i = from; i <= to; i++) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
}

int main() {
    int from, to;
    slave_primes();

    while (scanf("%d%d", &from, &to) != EOF) {
        calc(from, to);

        if (primes.size() <= 1) {
            printf("There are no adjacent primes.\n");
            continue;
        }

        int minV = 1e9;
        int maxV = 0;
        int minfrom, maxfrom, minto, maxto;

        for (int i = 1; i < primes.size(); ++i) {
            if (primes[i] - primes[i-1] < minV) {
                minV = primes[i] - primes[i-1];
                minfrom = primes[i-1];
                minto = primes[i];
            }
            if (primes[i] - primes[i-1] > maxV) {
                maxV = primes[i] - primes[i-1];
                maxfrom = primes[i-1];
                maxto = primes[i];
            }
        }

        printf("%d,%d are closest, %d,%d are most distant.\n",
            minfrom, minto, maxfrom, maxto);
    }
    return 0;
}
