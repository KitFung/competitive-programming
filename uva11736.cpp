#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 40;
const int MAXV = 300;

string variable[MAXV];
int variableC[MAXV];


unsigned long long char_arr_to_i(string c) {
    unsigned long long sum = 0;
    int len = c.length();
    for(int i = 0; i < len; ++i) {
        sum = (sum << 1) + c[i] - '0' ;
    }
    return sum;
}


int main() {

    int b, v, request;
    while(cin >> b >> v) {
        map<string, unsigned long long> varVV;

        for(int i = 0; i < v; ++i) {
            cin >> variable[i] >> variableC[i];
        }

        for(int i = 0; i < v; ++i) {
            string v = "";
            unsigned long long sum = 0;
            for(int j = 0; j < variableC[i]; ++j) {
                string t;
                cin >> t;
                v += t;
            }
            varVV[ variable[i] ] = char_arr_to_i(v);
        }

        cin >> request;
        for(int i = 0; i < request; ++i) {
            string temp;
            cin >> temp;

            cout << temp << "=";
            if(varVV.find(temp) != varVV.end())
                cout << varVV[temp];
            cout << endl;
        }

    }
    return 0;
}