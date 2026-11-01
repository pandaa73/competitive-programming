#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ll = long long;
using ld = long double;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k; cin >> n >> k;

    vector<array<int, 2>> v(n);
    for(auto &[x, y]: v) cin >> x >> y;

    for(int i = 1; i < n; ++i) {
        if(v[i][0] + 24-v[i-1][1] >= k) {
            cout << i-1 << endl;
            return 0;
        }
    }

    cout << -1 << endl;
    return 0;
}