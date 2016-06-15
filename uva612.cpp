#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct dna {
  char words[60];
  int val;
  bool operator < (const dna &b) {
    return val < b.val;
  }
} DNA[110];

int calval(int idx, int n) {
  int count = 0;
  for(int i = 0; i < n - 1; ++i) {
    for(int j = i + 1; j < n; ++j) {
      if(DNA[idx].words[i] > DNA[idx].words[j])
        count++;
    }
  }
  return count;
}

void insertion_sort(int m) {
  if(m < 2) return;

  for(int i = 1; i < m; ++i) {
    for(int j = i; j > 0; --j) {
      if(DNA[j] < DNA[j - 1])
        swap(DNA[j], DNA[j - 1]);
      else
        continue;
    }
  }
}

int main() {
  int ncase, n, m;
  scanf("%d", &ncase);
  for(int i = 0; i < ncase; ++i) {
    scanf("%d%d", &n, &m);
    for(int j = 0; j < m; ++j) {
      scanf("%s", DNA[j].words);
      DNA[j].val = calval(j, n);
    }

    insertion_sort(m);

    if(i > 0) printf("\n");
    for(int j = 0; j < m; ++j) {
      printf("%s\n", DNA[j].words);
    }
  }
  return 0;
}
