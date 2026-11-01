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
    map<int, int> mp;

    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        mp[x]++;
    }

    int cnt = 0;
    for(auto [k, v]: mp)
        if(v > 1) cnt++;

    cout << (cnt <= 1 ? "NO" : "YES") << lf; 
}