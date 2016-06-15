#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

map <string, int> joiner;
map<string, int> allproject;
vector< pair<string, vector<string> > > allsoftware;
vector< pair<string, int> > eve;

vector<string> curjoiner;
string curstring;
string curproject;
int counter;

bool pairCmp(const pair<string, int > &a, const pair<string, int > &b) {
  return a.second > b.second || (a.second == b.second && a.first.compare(b.first) < 0 );
}

void end_one_project() {
  if(!curproject.empty()) {
    allsoftware.push_back(make_pair(curproject, curjoiner));
  }
  curjoiner.clear();
}

void sumup_and_ready() {
  end_one_project();
  curproject = curstring;
  allproject[curproject] = 0;
}

void add_student_to_project() {
  if(joiner.find(curstring) == joiner.end()) {
    joiner[curstring] = 1;
    curjoiner.push_back(curstring);
  } else {
    if(find(curjoiner.begin(), curjoiner.end(), curstring) == curjoiner.end()) {
      curjoiner.push_back(curstring);
      joiner[curstring]++;
    }
  }
}

void cleanup() {
  end_one_project();

  for(int i = 0; i < allsoftware.size(); ++i) {
    int counter = 0;
    for(int j = 0; j < allsoftware[i].second.size(); ++j) {
      if(joiner[allsoftware[i].second[j]] == 1)
        counter++;
    }
    eve.push_back( make_pair(allsoftware[i].first, counter) );
  }

  sort(eve.begin(), eve.end(), pairCmp);
  for(int i = 0; i < eve.size(); ++i) {
    cout << eve[i].first << " " << eve[i].second << endl;
  }

  eve.clear();
  joiner.clear();
  allsoftware.clear();
  curproject.clear();
}

int main() {
  while( getline(cin, curstring) && curstring[0] != '0') {
    if(curstring[0] >= 'A' && curstring[0] <= 'Z') {
      sumup_and_ready();
    } else if(curstring[0] >= 'a' && curstring[0] <= 'z') {
      add_student_to_project();
    } else if(curstring[0] == '1') {
      cleanup();
    }
  }
  return 0;
}
