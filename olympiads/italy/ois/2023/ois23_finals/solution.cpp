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
    for(auto &x: v) {
        int a, b, c; 
        cin >> a >> b >> c;
        
        x = a+b+c;
    }

    int mx = 0;
    for(int i = 1; i < n; ++i)
        mx = max(mx, v[i]);

    mx += k*100;

    if(v[0] > mx) {
        cout << 0 << endl;
        return 0;
    }

    cout << mx-v[0]+1 << endl;
    return 0;
}