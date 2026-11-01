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

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n; cin >> n;

    vector<int> v(n);
    for(auto &x: v) cin >> x;
    
    auto solve = [&](int l, int r) {
        if(l == r) return (bool)1;

        stack<int> s;
        for(; l < r; ++l) {
            if(s.empty()) s.push(v[l++]);

            if((v[l] + s.top()) & 1)
                s.pop();
            else s.push(v[l]); 
        }

        return s.empty();
    };

    vector<int> ans;
    for(int c = 0; c < n; ++c)
        if(solve(0, c) && solve(c + 1, n))
            ans.push_back(v[c]);

    cout << ans.size() << lf;
    for(auto &x: ans) 
        cout << x << " ";
    cout << lf;
}