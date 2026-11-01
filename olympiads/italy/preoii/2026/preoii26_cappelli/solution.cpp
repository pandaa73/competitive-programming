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

long long acquista(int N, int M, int L, vector<int> X, vector<int> T) {
    sort(rall(X));

    multiset<int> s;
    for(auto x: T) {
        s.emplace(x);
    }

    ll ans = 0;
    for(auto x: X) {
        auto it = s.lower_bound(x);
        if(it == s.end() || *it >= x + L) continue;

        ans += L - *it + x;
        s.erase(it);
    }

    return ans;
}

#ifdef LOCAL

int main() {
    int N, M, L;

    cin>>N>>M>>L;

    vector<int> X(N), T(M);

    for(auto &x:X) cin>>x;
    for(auto &t:T) cin>>t;

    long long C = acquista(N, M, L, X, T);

    cout<<C<<"\n";
}

#endif /* LOCAL */
