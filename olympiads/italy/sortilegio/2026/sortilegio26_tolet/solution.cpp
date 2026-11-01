#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

int N;
vector<int> V;
vector<ll> px;

void acquista(int N, vector<int> P) {
    ::N = N;
    ::V = P;
    px.resize(N + 1);

    sort(V.rbegin(), V.rend());

    for(int i = 0; i < N; ++i) {
        px[i + 1] = px[i] + V[i];
    }
}

int ispeziona(int K, int T) {
    auto check = [&](int m) -> bool {
        return px[m] - (ll)V[m - 1] * m <= (ll)K * T;
    };

    int l = 1, r = N + 1;
    while(r - l > 1) {
        int m = (l + r) / 2;

        if(check(m)) {
            l = m;
        } else {
            r = m;
        }
    }

    ll x = px[l] - (ll)V[l - 1] * l;

    return (int)max({
        0LL,
        (ll)V[0] - T,
        V[l - 1] - ((ll)K * T - x) / l
    });
}
