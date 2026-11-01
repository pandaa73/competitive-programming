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

int squalifica(int N, vector<int> T, vector<int> L) {
    multiset<int> s;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    for(int i = 0; i < N; ++i) {
        while(!q.empty() && q.top().fi <= T[i]) {
            s.emplace(q.top().se); q.pop();
        }

        auto it = s.upper_bound(L[i]);
        if(it != s.begin()) s.erase(prev(it));

        q.emplace(T[i] + L[i], L[i]);
    }

    while(!q.empty()) {
        s.emplace(q.top().se); q.pop();
    }

    return s.size();
}

#ifdef LOCAL
int main() {
    int N;
    cin >> N;

    vector<int> T(N), L(N);

    for (int &i : T)
        cin >> i;
    for (int &i : L)
        cin >> i;

    cout << squalifica(N, T, L) << endl;
}
#endif
