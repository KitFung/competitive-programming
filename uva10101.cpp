#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int count = 0;
    long long input;
    while (cin >> input) {
        vector<string> output;

        if(input == 0) output.push_back("0");

        if(input > 0) {
            if(input % 100 != 0) {
                ostringstream ss;
                ss << (input % 100);
                output.push_back(ss.str());
            }
            input /= 100;
        }

        while (true) {

            if(input > 0) {
                if(input % 10 != 0) {
                    ostringstream ss;
                    ss << (input % 10);
                    output.push_back("shata");
                    output.push_back(ss.str());
                }
                input /= 10;
            } else {
                break;
            }

            if(input > 0) {
                if(input % 100 != 0) {
                    ostringstream ss;
                    ss << (input % 100);
                    output.push_back("hajar");
                    output.push_back(ss.str());
                }
                input /= 100;
            } else {
                break;
            }

            if(input > 0) {
                if(input % 100 != 0) {
                    ostringstream ss;
                    ss << (input % 100);
                    output.push_back("lakh");
                    output.push_back(ss.str());
                }
                input /= 100;
            } else {
                break;
            }

            if(input > 0) {
                output.push_back("kuti");
                if(input % 100 != 0) {
                    ostringstream ss;
                    ss << (input % 100);
                    output.push_back(ss.str());
                }
                input /= 100;
            } else {
                break;
            }
        }
        reverse(output.begin(), output.end());

        cout << setw(4) << ++count << ". ";
        for(int i = 0; i < output.size(); ++i) {
            if(i != 0) cout << " ";
            cout << output[i];
        }
        cout << endl;
    }
}
