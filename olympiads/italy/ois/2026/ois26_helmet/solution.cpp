#include <bits/stdc++.h>
#include <random>
using namespace std;

#define ff endl
#define lf "\n"
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infor
#undef infof

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;
using ld = long double;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int ask(int a, int b) {
    cout << "?" _ a _ b << ff;

    int x; cin >> x;
    return x;
}

void guess(int n) {
    cout << "!" _ n << ff;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<pll> V(N);
    for(auto &[a, b]: V) cin >> a >> b;

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    auto dist = [&](int i, int j) -> ll {
        auto [xi, yi] = V[i];
        auto [xj, yj] = V[j];

        ll d = (xi - xj) * (xi - xj) + (yi - yj) * (yi - yj);

        infof("... dist(%d, %d) = %lld", i, j, d);

        return d;
    };

    vector<int> idx(N), idx2; iota(all(idx), 0);
    while(idx.size() > 1) {
        uniform_int_distribution<int> dist_a(0, idx.size() - 1);
        uniform_int_distribution<int> dist_b(0, idx.size() - 2);

        int a = dist_a(rng);
        int b = dist_b(rng);
        if(b >= a) b++;

        infor("idx:");
        for(auto x: idx) {
            infor(" %d", x);
        }

        infof("");

        if(ask(idx[a], idx[b])) swap(a, b);

        for(auto i: idx) {
            if(dist(idx[a], i) <= dist(idx[b], i)) {
                idx2.emplace_back(i);
            }
        }

        swap(idx, idx2);
        idx2.clear();
    }

    guess(idx[0]);
}
