#include <bits/stdc++.h>
using namespace std;

#include <cassert>

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

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

vector<int> assegna(int N, int M, vector<vector<int>> S) {
    vec<vec<int>> V(M);
    for(int i = 0; i < N; ++i) {
        for(auto x: S[i]) {
            V[x].emplace_back(i);
        }
    }

    for(int x = 0; x < M; ++x) {
        V[x].emplace_back(N);
    }

    vec<int> cnt(M);
    vec<vec<int>> first(N + 1);
    for(int x = 0; x < M; ++x) {
        const auto &v = V[x];

        if(v.size() == 1) continue;

        cnt[x] = 1;
        first[v[0]].emplace_back(x);

        for(int i = 1; i < v.size() - 1; ++i) {
            if(v[i] - 1 != v[i - 1]) {
                cnt[x] += 1;
                first[v[i]].emplace_back(x);
            }
        }
    }

    queue<int> q;
    for(int x = 0; x < M; ++x) {
        if(cnt[x] == 0) q.emplace(x);
    }

    auto push = [&](int i) -> void {
        for(auto x: first[i]) {
            if(--cnt[x] == 0) {
                q.emplace(x);
            }
        }

        first[i].clear();
    };

    push(0);

    int value = M;
    vec<int> P(M);

    while(!q.empty()) {
        auto x = q.front();
        q.pop();

        P[x] = --value;

        const auto &v = V[x];
        for(int i = 0; i < v.size() - 1; ++i) {
            if(v[i] + 1 != v[i + 1]) {
                push(v[i] + 1);
            }
        }
    }

    return value == 0 ? P : vector<int>();
}

#ifdef LOCAL

int main() {

    int N, M;
    cin>>N>>M;

    vector<vector<int>> S(N);

    for(int i=0; i<N; i++) {
        int K;
        cin>>K;

        S[i].resize(K);

        for(int j=0; j<K; j++) {
            cin>>S[i][j];
        }
    }

    vector<int> P = assegna(N, M, S);

    cout<< size(P) << "\n";

    for(int i:P)
        cout<<i<<" ";
    cout<<"\n";
}

#endif /* LOCAL */
