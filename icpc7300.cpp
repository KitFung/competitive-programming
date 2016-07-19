#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAXN = 250;
char curStr[MAXN+10];

int hexToDec(char h) {
  if(h >= '0' && h <= '9') return h - '0';
  return h - 'A' + 10;
}

int main() {
  // freopen("input.txt", "r", stdin);
  while(scanf("%s\n", curStr) != EOF) {
    int len = strlen(curStr);
    for(int i = 0; i < len; i+=2) {
      printf("%c", hexToDec(curStr[i]) * 16 + hexToDec(curStr[i+1]));
    }
    printf("\n");
  }
  return 0;
}
