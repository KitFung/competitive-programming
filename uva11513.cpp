#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
using namespace std;

// brute force since 9P9 is small enough

map<string, bool> visited;
map<string, string> move_records;

// 0 - 3
string move_H(string s, int row) {
  int k = row * 3;
  char head = s[k];
  for(int i = 0; i < 2; ++i) {
    s[k + i] = s[k + i + 1];
  }
  s[k + 2] = head;
  return s;
}

string move_V(string s, int col) {
  char tail = s[col + 6];
  for(int i = 2; i >= 1; --i) {
    s[col + i*3] = s[col + (i-1)*3];
  }
  s[col] = tail;
  return s;
}

void pre_cal() {
  string initStatus = "123456789";
  visited[initStatus] = true;
  move_records[initStatus] = "";

  queue<string> Q;
  Q.push(initStatus);
  while(!Q.empty()) {
    string curstr = Q.front(); Q.pop();

    for(int i = 0; i < 3; ++i) {
      string news1 = move_V(curstr, i);
      if(visited.find(news1) == visited.end()) {
        visited[news1] = true;
        ostringstream temp;
        temp << (i+1);
        move_records[news1] = "V" + temp.str() + move_records[curstr];
        Q.push(news1);
      }
    }

    for(int i = 0; i < 3; ++i) {
      string news1 = move_H(curstr, i);

      if(visited.find(news1) == visited.end()) {
        visited[news1] = true;
        ostringstream temp;
        temp << (i+1);
        move_records[news1] = "H" + temp.str() + move_records[curstr];
        Q.push(news1);
      }
    }

  }

}

int main() {
  pre_cal();
  int n;
  string curcase;

  while(cin >> n) {
    if(n == 0) break;
    curcase.clear();
    curcase += (n + '0');

    for(int i = 0; i < 8; ++i) {
      cin >> n;
      curcase += (n + '0');
    }

    if(move_records.find(curcase) == move_records.end())
      cout << "Not solvable" << endl;
    else
      cout << move_records[curcase].length()/2 << " " << move_records[curcase] << endl;
  }
  return 0;
}
