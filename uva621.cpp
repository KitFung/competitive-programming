#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main() {
  int n;
  string in;
  cin >> n;
  for(int i = 0; i < n; ++i) {
    cin >> in;
    int len = in.length();

    if(in == "1" || in == "4" || in == "78")
      cout << '+' << endl;
    else if(in[len-2] == '3' && in[len-1] == '5')
      cout << '-' << endl;
    else if(in[0] == '9' && in[len-1] == '4')
      cout << '*' << endl;
    else
      cout << '?' << endl;
  }
  return 0;
}
