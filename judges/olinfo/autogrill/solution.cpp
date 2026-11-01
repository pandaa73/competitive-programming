#include <bits/stdc++.h>
using namespace std;

using ll = long long;

set<ll> v;
void inizia() {
    return;
}

void apri(ll p) {
    v.insert(p);
}

void chiudi(ll p) {
    v.erase(p);
}

ll chiedi(ll p) {
    if(v.empty()) return -1;
    auto lbound = v.lower_bound(p);
    if(lbound == v.end()) return *prev(lbound);

    ll a = *lbound;
    if(lbound != v.begin()) lbound--;
    ll b = *lbound;

    return (a-p <= p-b ? a : b);
}