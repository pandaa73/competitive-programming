#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ll = long long;
using ld = long double;

void solve() {
    int n; cin >> n;
    int pts = 0, mx = 0;
    for(int i = 0; i < n; ++i) {
        int p; cin >> p;
        switch(p) {
            case 1: pts += 25, mx += 18; break;
            case 2: pts += 18, mx += 25; break;
            case 3: pts += 15, mx += 25; break;
            case 4: pts += 12, mx += 25; break;
            case 5: pts += 10, mx += 25; break;
            case 6: pts +=  8, mx += 25; break;
            case 7: pts +=  6, mx += 25; break;
            case 8: pts +=  4, mx += 25; break;
            case 9: pts +=  2, mx += 25; break;
            case 10: pts += 1, mx += 25; break;
            default: pts += 0, mx += 25; break;
        }
    } cout << (pts >= mx ? "Champion" : "Practice harder") << endl;
}

int main() {
    int t; cin >> t;
    while(t--) solve();
}