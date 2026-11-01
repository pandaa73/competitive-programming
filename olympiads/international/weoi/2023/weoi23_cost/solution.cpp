#include <bits/stdc++.h>
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

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr int MOD = 1000003;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int mul(int a, int b) {
    return (ll)a * b % MOD;
}

void chmul(int &a, int b) {
    a = mul(a, b);
}

vec<int> counting_sort(int N, int K, const vec<int> &V) {
    vec<int> c(K + 1), p(N);
    for(int i = 0; i < N; ++i) c[V[i]] += 1;
    for(int i = 1; i <= K; ++i) c[i] += c[i - 1];
    for(int i = N - 1; i >= 0; i--) p[--c[V[i]]] = i;

    return p;
}

struct DSU {
    DSU(int N): dsu(N, -1), alive(N, 0), sq(0) {}

    int find(int n) {
        return dsu[n] < 0 ? n : dsu[n] = find(dsu[n]);
    }

    void join(int u, int v) {
        if(!alive[u] || !alive[v]) return;

        u = find(u);
        v = find(v);

        if(u == v) return;

        if(dsu[u] > dsu[v]) {
            swap(u, v);
        }

        chadd(sq, MOD - mul(dsu[u], dsu[u]));
        chadd(sq, MOD - mul(dsu[v], dsu[v]));

        dsu[u] += dsu[v];
        dsu[v] = u;

        chadd(sq, mul(dsu[u], dsu[u]));
    }

    void spawn(int n) {
        chadd(sq, 1);
        alive[n] = 1;
    }

    int sq;

    vec<int> dsu;
    vec<bool> alive;
};

int solve(int N, int M, int K, vector<int> A, vector<int> B) {
    auto p = counting_sort(N, K, A);
    auto q = counting_sort(M, K, B);

    DSU dsu_a(N), dsu_b(M);

    int ii = 0, jj = 0;
    int ans = 0, sum = 0;
    for(int k = 1; k <= K; ++k) {
        for(; ii < N && A[p[ii]] <= k; ++ii) {
            int i = p[ii];
            dsu_a.spawn(i);
            if(i >     0) dsu_a.join(i, i - 1);
            if(i < N - 1) dsu_a.join(i, i + 1);
        }

        for(; jj < M && B[q[jj]] <= k; ++jj) {
            int j = q[jj];
            dsu_b.spawn(j);
            if(j >     0) dsu_b.join(j, j - 1);
            if(j < M - 1) dsu_b.join(j, j + 1);
        }

        int cnt = add(mul(dsu_a.sq, dsu_b.sq), MOD - sum);

        chadd(ans, mul(k, cnt));
        chadd(sum, cnt);
    }

    return ans;
}

#ifdef LOCAL

#include <iostream>
#include <vector>

using namespace std;

int solve(int N, int M, int K, vector<int> A, vector<int> B);

int main() {
  ios_base::sync_with_stdio(false);
  // If you prefer file IO, uncomment the following two lines.
  //
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);

  int N, M, K;
  cin >> N >> M >> K;

  vector<int> A(N);
  vector<int> B(M);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (int i = 0; i < M; i++) {
    cin >> B[i];
  }

  cout << solve(N, M, K, A, B) << endl;

  return 0;
}

#endif
