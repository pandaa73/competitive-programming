#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ll = long long;
using ld = long double;

void solve() {
    string s; cin >> s;
    int c0, c2, c5, c7;
    c0 = c2 = c5 = c7 = 0;

    for(const auto& c: s) {
        switch(c) {
            case '0': ++c0; break;
            case '2': ++c2; break;
            case '5': ++c5; break;
            case '7': ++c7; break;
        }
    }

    if(s.length() == 1) {
        cout << -1 << endl;
        return;
    }

    int ans = 3;
    if(c0 >= 2) {
        int mn = 2;
        if(s.back() == '0') mn--;
        if(s[s.length()-2] == '0') mn--;

        ans = min(mn, ans);
    }

    if(c2 >= 1 && c5 >= 1) {
        int mn = 2;
        if(s.back() == '5') mn--;
        if(s[s.length()-2] == '2') mn--;

        if(s.back() == '2' && s[s.length()-2] == '5') mn = 1;

        ans = min(mn, ans);
    }

    if(c5 >= 1 && c0 >= 1) {
        int mn = 2;
        if(s.back() == '0') mn--;
        if(s[s.length()-2] == '5') mn--;

        if(s.back() == '5' && s[s.length()-2] == '0') mn = 1;

        ans = min(mn, ans);
    }

    if(c7 >= 1 && c5 >= 1) {
        int mn = 2;
        if(s.back() == '5') mn--;
        if(s[s.length()-2] == '7') mn--;

        if(s.back() == '7' && s[s.length()-2] == '5') mn = 1;

        ans = min(mn, ans);
    }

    cout << (ans == 3 ? -1 : ans) << endl;
}

int main() {
    int t; cin >> t;
    while(t--) solve();
}