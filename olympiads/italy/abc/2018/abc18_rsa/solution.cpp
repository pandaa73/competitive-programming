#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll fexp(ll b, ll e, ll m) {
    ll ans = 1;
    while(e > 0) {
        if(e & 1)
            ans *= b, ans %= m;
        b *= b, b %= m;
        e >>= 1;
    } return ans;
}

void decifra(int m, int e, int n, int v[], char d[]) {
    for(int i = 0; i < n; ++i)
        d[i] = fexp(v[i], e, m);

    d[n] = '\0';
}