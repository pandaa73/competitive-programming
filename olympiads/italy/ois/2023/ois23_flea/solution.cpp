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
    
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        char c; cin >> c;
        ans += (c == 'L' ? -1 : 1);
    }

    cout << abs(ans) << endl;
    return 0;
}