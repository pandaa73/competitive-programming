#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

void solve(void) {
    string ans = "-----";

    auto ask = [&](string q) -> string {
        cout << "?" _ q << ff;

        return cin >> q, q;
    };

    string x = "";
    x += ask("abcde");
    x += ask("fghij");
    x += ask("klmno");
    x += ask("pqrst");
    x += ask("uvwxy");

    auto get_idx = [&](char c) -> int { return (c - 'a') % 5; };

    vector<char> y;
    for(int i = 0; i < x.size(); ++i) {
        auto &c = x[i];

        if(c == 'Y' || c == 'G') y.push_back(i + 'a');
        if(c == 'G') ans[get_idx(i + 'a')] = i + 'a';
    }

    char last = 'z';
    for(int i = 0; i < y.size(); ++i) {
        if(i == 4) {
            last = y[i];
            continue;
        }

        int z = get_idx(y[i]);

        string q(5, y[i]); q[z] = 'z';
        q = ask(q);

        for(int j = 0; j < q.size(); ++j)
            if(q[j] == 'G')
                ans[j] = j == z ? 'z' : y[i];
    }

    for(auto &c: ans)
        if(c == '-') c = last;

    cout << "!" _ ans << ff;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) solve();
}
