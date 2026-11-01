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
    
    vector<int> v(n);
    for(auto &x: v) cin >> x;

    sort(all(v));

    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(v[i]+v[i+1] <= k)
            ++cnt, ++i;
        else ++cnt;
    }

    cout << cnt << endl;
    return 0;
}