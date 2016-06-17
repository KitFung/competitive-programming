#include <cstdio>
#include <iostream>
#include <cstring>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

int words[26];

int main() {
  // freopen("input.txt", "r", stdin);

  int n;
  int len;
  int cc;
  string input;

  cin >> n;
  for(int i = 0; i < n; ++i) {
    memset(words, 0, sizeof(words));

    cc = 0;
    cin >> input;
    len = input.size();

    for(int j = 0; j < input.length(); ++j) {
      words[input[j] - 'a']++;
    }
    int minv = 999999;

    for(int j = 0; j < 26; ++j) {
      minv = min(minv, words[j]);
    }
    printf("Case %d: %d\n", i+1, minv);

  }
}
