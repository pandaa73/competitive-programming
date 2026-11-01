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

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

struct DSU {
    DSU(int N): T(N, -1) {}

    int find(int n) {
        return T[n] < 0 ? n : T[n] = find(T[n]);
    }

    bool join(int u, int v) {
        u = find(u);
        v = find(v);

        if(u == v) return 0;
        if(T[u] > T[v]) swap(u, v);

        T[u] += T[v];
        T[v] = u;

        return 1;
    }

    vec<int> T;
};

int progetta(int N, int M, int K, vector<int> &A, vector<int> &B,
        vector<int> &W) {
    vec<int> ord(M);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) -> bool {
        return W[i] > W[j];
    });

    DSU dsu(N);
    int s = 0, c = N;
    for(auto e: ord) {
        if(dsu.join(A[e] - 1, B[e] - 1)) {
            s += W[e];
            if(--c == K) break;
        }
    }

    return s;
}

#ifdef LOCAL

int main(){
	int N, M, K;
	cin>>N>>M>>K;
	vector<int> A(M), B(M), W(M);
	for(int i=0;i<M;i++)
		cin>>A[i]>>B[i]>>W[i];
	int score=progetta(N,M,K,A,B,W);
	cout<<score<<endl;
	return 0;
}

#endif /* LOCAL */
