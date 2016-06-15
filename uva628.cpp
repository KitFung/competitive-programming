#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> words;


void print_ans(string templa, int curidx, string ans) {
  int len = templa.length();
  if(curidx == len) cout << ans << endl;

  if(templa[curidx] == '#') {
    for(int i = 0; i < words.size(); ++i) {
      string temp = ans;
      temp += words[i];
      print_ans(templa, curidx + 1, temp);
    }
  }else if(templa[curidx] == '0') {
    for(int i = 0; i < 10; ++i) {
      string temp = ans;
      temp += (char)(i + '0');
      print_ans(templa, curidx + 1, temp);
    }
  }
}

int main() {
  int nwords, ntemplate;
  string in;
  while(cin >> nwords) {
    words.clear();

    cout << "--" << endl;
    for(int i = 0; i < nwords; ++i) {
      cin >> in;
      words.push_back(in);
    }

    cin >> ntemplate;
    for(int i = 0; i < ntemplate; ++i) {
      cin >> in;
      print_ans(in, 0, "");
    }
  }
  return 0;
}
