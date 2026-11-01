#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ll = long long;
using ld = long double;

int main() {
    ll n, k; cin >> n >> k;
    ll sum = 0, avg = n*k;
    vector<ll> v(n); for(auto& x: v) cin >> x, sum += x;

    if(sum == avg) {
        cout << 0 << endl;
        return 0;
    } ll tg = (ll)ceil(((ld)avg-(ld)sum)/(ld)n);

    if(sum < avg) {
        cout << tg << endl;
        return 0;
    } // tg = -tg;

    sort(all(v));
    ll tk = 0;
    for(int i = 0; i < n; ++i) {
        if(v[i]-tg < 1) {
            tk += v[i]-1;
            v[i] = 1;
        } else tk += tg, v[i] -= tg;
    } if(tk >= sum-avg) cout << tg << endl;

    ll l, r;
    for(int i = 0; i < n; ++i) {
        l = 0, r = v[i]-1;
        if(v[i] == 1) continue;
        if((n-i)*r+tk < sum-avg) {
            tk += r;
            v[i] = 1;
            continue;
        }

        while(r-l>1) {
            ll m = (l+r)/2;
            if((n-i)*m+tk < sum-avg) 
                l = m;
            else r = m;
        }

        break;
    } 
    
    cout << tg+r << endl;
}