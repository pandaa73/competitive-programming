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

    int n; cin >> n;
    
    vector<int> v(n);
    for(auto &x: v) cin >> x;

    int ans = 0;
    for(int i = 1; i < n; ++i) {
        if(v[i] == v[i-1]+1)
            continue;

        if(v[i] == 1 && v[i-1] == n) {
            ans = (n-i)%n;
            continue;
        }

        ans = -1;
        break;
    }
    
    cout << ans << endl;
    return 0;
}