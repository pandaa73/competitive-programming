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

    vector<string> v(n);
    for(auto &x: v) cin >> x;

    sort(v.begin(), v.end(), [&](const string &a, const string &b) {
        if(a.size() == b.size())
            return a > b;
        return a.size() < b.size(); 
    });

    auto jumpable = [&](string a, string b) -> bool {
        if(b.size() == a.size() - 1) {
            int i, j; i = j = 0;

            for(; i < a.size(); ++i, ++j) {
                if(a[i] == b[j]) continue;

                if(i != j || a[++i] != b[j]) return 0;
            }

            return 1;

        } else if(a.size() != b.size()) return 0;

        bitset<26> vis;

        int cnt = 0;
        for(int i = a.size() - 1; i >= 0; vis[a[i--] - 'a'] = 1) {
            if(a[i] == b[i]) continue;

            if(b[i] > a[i] && vis[b[i] - 'a'] == 1)
                cnt++;
            else return 0;
        }

        if(cnt > 1)
            return 0;
        return 1;
    };

    vector<int> ans(n, 0);
    for(int i = 0; i < n; ++i) {
        int mx = 0;
        for(int j = 0; j < i; ++j) {
            if(jumpable(v[i], v[j]))
                mx = max(mx, ans[j]);
        }

        ans[i] = mx + 1;
    }
    
    int mx = 0;
    for(auto x: ans)
        mx = max(mx, x);

    cout << mx << lf;
}