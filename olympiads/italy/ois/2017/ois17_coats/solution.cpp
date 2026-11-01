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

    vector<int> v(n);
    for(auto &x: v) cin >> x;

    ll lifts = 0;
    ll coats = 0;

    for(int i = 0, cnt = 0; i < n; ++i) {
        coats += v[i];
        if(v[i] == 2) lifts += ++cnt;
    }

    cout << (float)lifts / (float)coats << lf;
}
