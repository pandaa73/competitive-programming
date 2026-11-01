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
   
    vector<array<int, 2>> v(n);
    for(auto &[x, _]: v)
        cin >> x;
    for(auto &[_, y]: v)
        cin >> y;
        
    bool f = 0;
    int mn = INT_MAX;
    int sm1 = 0, sm2 = 0;
    for(auto [a, b]: v) {
        if(a < mn)
            mn = a, f = 0;
        if(b < mn)
            mn = b, f = 1;

        sm1 += a; sm2 += b;
    }

    cout << (sm1 < sm2 ? "Hamilton" : "Verstappen") << endl;
    cout << (!f ? "Hamilton" : "Verstappen") << endl;
    return 0;
}