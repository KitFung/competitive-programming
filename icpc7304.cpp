#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

typedef long long LL;
const int MOD = 1000000007;

map<int, int> countv;
// vector<int> dheight;

int dfs(int digit, int minheight, int need_die) {
	if (digit == 0) return need_die == 0;
	if (digit < need_die) return 0;
	if (need_die == 0) {
		for (map<int, int>::iterator i = countv.begin(); i != countv.end(); ++i) {
			if (i->second > 0 && i->first > minheight) return 0;
		}
		return 1;
	}

	int sum = 0;
	int new_need_die;

	for (map<int, int>::iterator i = countv.begin(); i != countv.end(); ++i) {
		if (i->second == 0) continue;

		new_need_die = need_die - (minheight != -1 && i->first > minheight);
		countv[i->first]--;
		sum += dfs(digit - 1, minheight==-1?(i->first):min(i->first, minheight), new_need_die);
		countv[i->first]++;
		sum %= MOD;
	}
	return sum;
}

int main() {
	freopen("input.txt", "r", stdin);
	int T, N, K;
	int h;
	scanf("%d", &T);
	for (int nt = 1; nt <= T; ++nt) {
		countv.clear();
		// dheight.clear();
		scanf("%d%d", &N, &K);
		for (int nn = 0; nn < N; ++nn) {
			scanf("%d", &h);
			// if(countv[h] == 0) {
			// 	dheight.push_back(h);
			// }
			countv[h]++;
		}
		// sort(dheight.begin(), dheight.end());
		printf("Case %d: %d\n", nt, dfs(N, -1, K));
	}
	return 0;
}
