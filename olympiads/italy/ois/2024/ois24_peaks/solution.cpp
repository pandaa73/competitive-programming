#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x), rend(x)

using ll = long long;
using ld = long double;

int main() {
    ll n, m; cin >> n >> m;

    vector<ll> a(n), b(m);
    for(auto& x: a) cin >> x;
    for(auto& x: b) cin >> x;

    ll pa = 0, pb = 0;
    if(n > 1 && a[0] > a[1]) ++pa;
    if(m > 1 && b[0] > b[1]) ++pb;

    if(n > 1 && a.back() > a[a.size()-2]) ++pa;
    if(m > 1 && b.back() > b[b.size()-2]) ++pb;

    for(int i = 1; i < n-1; ++i) {
        if(a[i] > a[i-1] && a[i] > a[i+1]) ++pa;
    } 

    for(int i = 1; i < m-1; ++i) {
        if(b[i] > b[i-1] && b[i] > b[i+1]) ++pb;
    }

    if(n == 1) pa = 1;
    if (m==1) pb=1;
    // Cappiello
    cout << pa * pb << endl;
}
