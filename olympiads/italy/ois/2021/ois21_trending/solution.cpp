#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e6+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int dp[N];

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, t; cin >> n >> t;

    queue<string> q;
    map<string, int> mp;
    set<pair<int, string>> s;

    auto add = [&](string x) {
        q.push(x);

        if(mp[x])
            s.erase({-mp[x], x});

        s.insert({-++mp[x], x});
    };

    auto remove = [&](string x) {
        s.erase({-mp[x], x});

        if(--mp[x])
            s.insert({-mp[x], x});
    };

    for(int i = 0; i < t; ++i) {
        string x; cin >> x;
    
        add(x);
    }

    for(; t < n; ++t) {
        cout << s.begin()->second << lf;

        string x; cin >> x;

        add(x);

        string y = q.front(); q.pop();

        remove(y);
    }

    cout << s.begin()->second << lf;
}