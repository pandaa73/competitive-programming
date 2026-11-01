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
    vector<ll> v(n, 0);

    ll sum;
    int idx, mx;
    for(int i = 0; i < n; ++i) {
        sum = mx = 0;
        
        for(int j = 0; j <= n; ++j) {
            int x; cin >> x;
            if(x < 0) {
                idx = j;
                continue;
            }

            sum += x;
            if(j == n) break;
            if(v[mx] < v[j]) mx = j;
        }

        v[idx] += sum;
        if(v[mx] < v[idx]) mx = idx;
    
        cout << 1 + mx << lf;
    }
}