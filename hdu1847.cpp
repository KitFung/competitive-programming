#include <cstdio>
#include <cstring>

#define MAXN 1010

/**

当 g(x)=k 时，表明对于任意一个 0≤i<k，都存在 x 的一个后继 y 满足 g(y)=i。也就是说，当某枚棋子的 SG 值 是 k 时，我们可以把它变成 0、变成 1、⋯、变成 k−1，但绝对不能保持 k 不变。不知道你能不能根据这个联想到Nim游戏，Nim游戏的规则就是：每次 选择一堆数量为 k 的石子，可以把它变成 0、变成 1、…、变成 k−1，但绝对不能保持 k不变。这表明，如果将 n 枚棋子所在的顶点的 SG值看 作 n 堆相应数量的石子，那么这个Nim游戏的每个必胜策略都对应于原来这 n 枚棋子的必胜策略！这也与以下结论(Sprague-Grundy Theorem)相对应：

**/

int SG[MAXN], able[MAXN], f[MAXN];
const int choose = 9;

void init() {
    f[0] = 1;
    for(int i = 1; i <= choose; ++i)
        f[i] = f[i-1]*2;
}

void GetSG(int n) {
    memset(SG, 0, sizeof(SG));

    for(int i = 0; i <= n; ++i) {
        memset(able, 0, sizeof(able));
        for(int j = 0; j <= choose && f[j] <= i; ++j)
            able[SG[i-f[j]]] = 1;

        for(int j = 0; j <= n; ++j)
            if(!able[j]) {
                SG[i] = j;
                break;
            }
    }

}

int main() {
    init();
    GetSG(MAXN);

    int n;
    while(scanf("%d", &n) != EOF) {
        if(SG[n] != 0)
            printf("Kiki\n");
        else
            printf("Cici\n");
    }
    return 0;
}