#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    string v[n]; for(auto &x: v) cin >> x;
    string c[10]; for(auto &x: c) cin >> x;
    
    for(int i = 0; i < n; ++i) {
        string s = "";
        string m = "";

        for(int j = 0; j < v[i].size(); ++j) {
            m += v[i][j];

            for(int k = 0; k < 10; ++k) {
                if(m == c[k]) {
                    m = "";
                    s += k + 0x30;
                    break;
                }
            }
        }

        cout << s << lf;
    }
}