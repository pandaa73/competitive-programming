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

    int b; cin >> b;
    vector<string> bad(b);
    for(auto &x: bad) cin >> x;

    int g; cin >> g;
    vector<string> good(g);
    for(auto &x: good) cin >> x;

    int n; cin >> n;

    int gbcnt = 0, ggcnt = 0;
    for(int i = 0; i < n; ++i) {
        unordered_map<string, int> mp;

        int e; cin >> e;

        string s;
        while(e--) cin >> s, mp[s]++;

        int bcnt = 0;
        for(int j = 0; j < b; ++j) {
            if(!mp[bad[j]]) continue;
            
            bcnt = 1;
            break;
        }

        int gcnt = 0;
        for(int j = 0; j < g; ++j) {
            if(!mp[good[j]]) continue;
            
            gcnt = 1;
            break;
        }

        if(bcnt == gcnt) continue;

        (bcnt > gcnt ? gbcnt : ggcnt)++;
    }

    cout << gbcnt _ ggcnt << lf;
}