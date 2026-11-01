#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define lf "\n"
#define ff endl
#define fi first
#define se second
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

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

void solve(void) {
    int N; cin >> N;

    priority_queue<pii> q;
    for(int i = 0; i < N; ++i) {
        int x; cin >> x;

        if(x) q.emplace(x, i);
    }

    vector<int> V(N);
    for(int i = 0; i < N; ++i) {
        stack<pii> s;

        int x, j = i;
        while(j == i) {
            auto [y, k] = q.top(); q.pop();

            x = y, j = k;
            s.emplace(y, k);
        }

        V[i] = s.top().se;
        s.top().fi -= 1;

        while(!s.empty()) {
            auto p = s.top(); s.pop();

            q.emplace(p);
        }
    }

    static int t = 1;
    cout << "Case #" << t++ << ":";
    for(auto x: V) {
        cout << " " << x;
    }

    cout << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
