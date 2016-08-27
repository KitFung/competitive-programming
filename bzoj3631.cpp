#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define leftIdx (idx<<1)
#define rightIdx ((idx<<1)|1)
const int MAXN = 3e5+10;

int arr[MAXN];


int eidx;
int head[MAXN];
struct edge
{
    int to, nxt;
} E[MAXN << 1];

void add_two_edge(int from, int to) {
    E[eidx].to = to;
    E[eidx].nxt = head[from];
    head[from] = eidx++;
    E[eidx].to = from;
    E[eidx].nxt = head[to];
    head[to] = eidx++;
}


int fathers[MAXN], deeps[MAXN], sizes[MAXN];
int heaviest[MAXN];
int numIdx;
int num[MAXN], top[MAXN];
void dfs_1(int x, int father, int deep) {
    fathers[x] = father; deeps[x] = deep; sizes[x] = 1;

    int heavy = 0;
    for(int i = head[x]; i != -1; i = E[i].nxt) {
        int v = E[i].to;
        if(v != father) {
            dfs_1(v, x, deep+1);
            sizes[x] += sizes[v];
            if(heavy < sizes[v]) {
                heavy = sizes[v];
                heaviest[x] = v;
            }
        }
    }
}

void dfs_2(int x, int father) {
    top[x] = (heaviest[father] != x)?x:top[father];
    num[x] = ++numIdx;

    if(heaviest[x]) dfs_2(heaviest[x], x);

    for(int i = head[x]; i != -1; i = E[i].nxt) {
        int v = E[i].to;
        if(v != father && v != heaviest[x])
            dfs_2(v, x);
    }
}

struct treeNode {
    int sum, delta;
} T[MAXN << 1];

void update(int idx) {
    T[idx].sum = T[leftIdx].sum + T[rightIdx].sum;
}

void pushDown(int idx, int L, int R, int mid) {
    if(T[idx].delta) {
        T[leftIdx].sum += T[idx].delta * (mid - L + 1);
        T[leftIdx].delta = T[idx].delta;
        T[rightIdx].sum += T[idx].delta * (R - mid);
        T[rightIdx].delta = T[idx].delta;
        T[idx].delta = 0;
    }
}

void addOneToRange(int idx, int L, int R, int LRange, int RRange) {
    if(LRange <= L && R <= RRange) {
        T[idx].sum += (R-L+1);
        T[idx].delta++;
        return;
    }

    int mid = (L+R) >> 1;
    pushDown(idx, L, R, mid);

    if(LRange <= mid) addOneToRange(leftIdx, L, mid, LRange, RRange);
    if(mid < RRange) addOneToRange(rightIdx, mid+1, R, LRange, RRange);
}

int query(int idx, int L, int R, int LRange, int RRange) {
    if(LRange <= L && R <= RRange) {
        return T[idx].sum;
    }
    int mid = (L+R) >> 1;
    pushDown(idx, L, R, mid);
    int val = 0;
    if(LRange <= mid) val += query(leftIdx, L, mid, LRange, RRange);
    if(mid < RRange) val += query(rightIdx, mid+1, R, LRange, RRange);
    return val;
}

void insert(int u, int v) {
    int tu = top[u], tv = top[v];
    while(tu != tv) {
        if(deeps[tu] < deeps[tv]) {
            swap(u, v);
            swap(tu, tv);
        }

        addOneToRange(1, 1, numIdx, num[tu], num[u]);

        u = fathers[tu];
        tu = top[u];
    }
    if(num[u] > num[v]) swap(u, v);
    addOneToRange(1, 1, numIdx, num[u], num[v]);
}

void init() {
    eidx = 0;
    memset(head, -1, sizeof(head));
}

int main() {
    freopen("input.txt", "r", stdin);
    init();

    int nHouse;
    int from, to;

    scanf("%d", &nHouse);
    for(int i = 1; i <= nHouse; ++i) scanf("%d", &arr[i]);
    for(int i = 1; i < nHouse; ++i) {
        scanf("%d%d", &from, &to);
        add_two_edge(from, to);
    }

    dfs_1(1, 0, 1);
    dfs_2(1, 0);
    for(int i = 1; i < nHouse; ++i) insert(arr[i], arr[i+1]);

    for(int i = 1; i <= nHouse; ++i) {
        int ans = 0;
        ans -= (arr[i] != 1);
        ans += query(1, 1, numIdx, num[i], num[i]);
        printf("%d\n", ans);
    }


    return 0;
}