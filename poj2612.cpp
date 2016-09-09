#include <cstdio>
#include <cstring>

#define MAXN 11

int table[MAXN][MAXN];
bool ismine[MAXN][MAXN];
int n;

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

void add_bomb(int x, int y) {
    ismine[x][y] = true;
    if(valid(x+1, y)) table[x+1][y]++;
    if(valid(x-1, y)) table[x-1][y]++;
    if(valid(x, y+1)) table[x][y+1]++;
    if(valid(x, y-1)) table[x][y-1]++;
    if(valid(x+1, y+1)) table[x+1][y+1]++;
    if(valid(x-1, y+1)) table[x-1][y+1]++;
    if(valid(x+1, y-1)) table[x+1][y-1]++;
    if(valid(x-1, y-1)) table[x-1][y-1]++;
}

int main() {
    // freopen("input.txt", "r", stdin);

    while(scanf("%d\n", &n) != EOF) {
        memset(table, 0, sizeof(table));
        memset(ismine, false, sizeof(ismine));
        char c;

        for(int y = 0; y < n; ++y){
            for(int x = 0; x < n; ++x) {
                scanf("%c", &c);
                if(c == '*')
                    add_bomb(x, y);
            }
            scanf("\n");
        }

        for(int y = 0; y < n; ++y){
            for(int x = 0; x < n; ++x) {
                scanf("%c", &c);
                if(c == 'x')
                    if(ismine[x][y])
                        printf("*");
                    else
                        printf("%d", table[x][y]);
                else
                    printf(".");
            }
            scanf("\n");
            printf("\n");
        }

    }
    return 0;
}