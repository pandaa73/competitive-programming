#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> fft;

ll sum(int i) {
    ll ans = 0;
    for(; i > 0; i -= i & -i) ans += fft[i];

    return ans;
}

ll sum(int l, int r) {
    return sum(r) - sum(l);
}

void fset(int i, int n) {
    for(++i; i <= n; i += i & -i) fft[i] += 1;
}

ll paletta_sort(int n, int v[]) {
    vector<ll> p, d;
    for(int i = 0; i < n; ++i) {
        if(i&1) d.push_back(v[i]);
        else p.push_back(v[i]);
    }

    ll ans = 0;

    fft.resize(n+1); fill(fft.begin(), fft.end(), 0);
    for(auto x: p) {
        if(x&1) return -1;
        ans += sum(x, n);
        fset(x, n);
    }
    fill(fft.begin(), fft.end(), 0);
    for(auto x: d) {
        if(!x&1) return -1;
        ans += sum(x, n);
        fset(x, n);
    }

    return ans;
}