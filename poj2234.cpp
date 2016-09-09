#include <cstdio>
using namespace std;


int main() {
    int M, n;
    while(scanf("%d", &M) != EOF) {
        int ans = 0;

        for(int i = 0; i < M; ++i) {
            scanf("%d", &n);
            ans ^= n;
        }

        printf("%s\n", ans==0?"No":"Yes");
    }
    return 0;
}