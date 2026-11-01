#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<
#define lf "\n"

using ll = long long;

ll alleggerisci(int n, int m, vector<int> v, vector<int> l,
   vector<int> r, vector<ll> k) {
    vector<array<ll, 3>> sus;
    for(int i = 0; i < m; ++i) {
        sus.push_back({r[i], l[i], k[i]});
    }

    sort(begin(sus), end(sus));

    ll ans = 0;
    ll pfx[n + 1]; memset(pfx, 0x00, sizeof(pfx));

    int j = 0;
    for(int i = 0; i < n; ++i) {
        pfx[i + 1] = pfx[i] + v[i];

        while(i == sus[j][0]) {
            auto [cr, cl, x] = sus[j];
            ll sussone = (pfx[cr + 1] - pfx[cl]) - x;
            
            if(sussone > 0) {
                pfx[i + 1] -= sussone;
                ans += sussone;
            }

            j++;
            if(j == m) break;
        }
    }

    return ans;
}