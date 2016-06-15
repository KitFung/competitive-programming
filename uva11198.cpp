#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int len = 8;

const int LEFT = 0;
const int RIGHT = 1;

vector<int> inp;
map <int, bool> visited;
bool isprime[20];

void slave_prime() {

    memset(isprime, true, sizeof(isprime));

    isprime[0] = isprime[1] = false;
    for(int i = 4; i < 20; i+=2)
        isprime[i] = false;

    int limit = sqrt(20) + 1;
    for(int i = 3; i < limit; i+=2) {
        if(isprime[i]) {
            for(int j = i * 2; j < 20; j += i)
                isprime[j] = false;
        }
    }
}

int getOrd(vector<int> a) {
    int sum = 0;

    for(int i = 0; i < 8; ++i) {
        sum *= 10;
        sum += abs(a[i]);
    }
    return sum;
}

vector<int> dance(const vector<int>& v, int idxA, int idxB, int pos) {
    vector<int> newv(v);
    int i, counter = 0;
    int vb = newv[idxB];
    if(pos == LEFT) { // move B to A left
        if(idxA < idxB) {
            for(int i = idxB; i >= idxA + 1 ; --i) {
                newv[i] = newv[i - 1];
            }
            newv[idxA] = vb;
        } else {
            for(int i = idxB; i <= idxA - 1 ; ++i) {
                newv[i] = newv[i + 1];
            }
            newv[idxA - 1] = vb;
        }
    } else { // move B to A right
        if(idxA < idxB) {
            for(int i = idxB; i >= idxA + 1 ; --i) {
                newv[i] = newv[i - 1];
            }
            newv[idxA + 1] = vb;
        } else {
            for(int i = idxB; i <= idxA - 1 ; ++i) {
                newv[i] = newv[i + 1];
            }
            newv[idxA] = vb;
        }
    }
    return newv;
}

bool able_to_dance(int a, int b) {
    if (a==b || !isprime[abs(a)+abs(b)]) return false;
    return (a > 0 && b < 0) || (a < 0 && b > 0);
}

int bfs(vector<int> init) {
    visited.clear();
    queue< vector<int> > arrQ;
    queue<int> countQ;

    arrQ.push(init);
    countQ.push(0);
    visited[getOrd(init)] = true;

    while(!arrQ.empty()) {
        vector<int> arr = arrQ.front(); arrQ.pop();
        int count = countQ.front(); countQ.pop();
        int hashedV = getOrd(arr);

        if(hashedV == 12345678)
            return count;

        for(int i = 0; i < len; ++i)
            for(int j = 0; j < len; ++j)
                if(able_to_dance(arr[i], arr[j]))
                    for (int k = 0; k < 2; ++k) {
                        vector<int> newv = dance(arr, i, j, k);
                        if(visited.find(getOrd(newv)) == visited.end())  {
                            visited[getOrd(newv)] = true;
                            arrQ.push(newv);
                            countQ.push(count + 1);
                        }
                    }
    }

    return -1;
}


int main() {
    int n = 0, counter = 1;
    slave_prime();

    while(scanf("%d", &n) != EOF && n != 0) {
        inp.clear();
        inp.push_back(n);
        for(int i = 0; i < len - 1; ++i) {
            scanf("%d", &n);
            inp.push_back(n);
        }

        printf("Case %d: %d\n", counter++, bfs(inp));
    }
    return 0;
}
