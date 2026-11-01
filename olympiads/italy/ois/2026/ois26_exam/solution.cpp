#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vector<int> C(M);
    for(auto &x: C) cin >> x;

    vector<vector<pii>> V(N);
    for(auto &v: V) {
        int K; cin >> K;
        v.resize(K);
        for(auto &[p, s]: v) cin >> p >> s;
    }

    vector<int> ptr(N);
    vector<int> cut(M, 0);
    vector<priority_queue<pii, vector<pii>, greater<pii>>> q(M);
    auto push = [&](int i, auto &&push) -> void {
        if(ptr[i] == V[i].size()) return;

        auto [p, s] = V[i][ptr[i]++];

        q[p].emplace(s, i);
        if(q[p].size() > C[p]) {
            cut[p] = max(cut[p], q[p].top().fi + 1);
        }

        while(!q[p].empty() && q[p].top().fi < cut[p]) {
            int j = q[p].top().se; q[p].pop();
            push(j, push);
        }
    };

    for(int i = 0; i < N; ++i) {
        push(i, push);
    }

    for(int i = 0; i < M; ++i) {
        cout << cut[i] << " ";
    }

    cout << lf;
}
