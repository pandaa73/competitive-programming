#include <bits/stdc++.h>
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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int illumina(int N, int M, vector<int> H, vector<int> A, vector<int> B, vector<int> L) {
    int c = 1;
    vector<int> vis(N);
    vector<vector<int>> adj(N);

    for(int i = 0; i < M; ++i) {
        int u = A[i], v = B[i];

        if(H[u] > H[v]) swap(u, v);
        if(vis[u]) swap(u, v);
        if(vis[u]) continue;

        int x = H[u], y = H[v], w = L[i];

        if(w >= x + y)
            vis[u] = vis[v] = c;
        else if(w >= x && (w < y || y == 0))
            vis[u] = c;
        else if(w >= x) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    auto dfs = [&](int v, int f, int &n, int &e, auto &&dfs) -> void {
        n++;

        vis[v] = c;

        for(auto u: adj[v]) {
            e += u != f;

            if(!vis[u]) dfs(u, v, n, e, dfs);
        }
    };

    int ans = N;

    for(int i = 0; i < N; ++i) {
        if(vis[i]) continue;

        c++;
        int n = 0, e = 0;
        dfs(i, -1, n, e, dfs);

        if(e < n) ans--;
    }

    return ans;
}

// GRADER DI ESEMPIO, NON MODIFICARE

#ifndef EVAL

int main() {
	int N; cin >> N;
	int M; cin >> M;

	vector<int> H(N);
	for (int i = 0; i < N; ++i)
		cin >> H[i];

	vector<int> A(M), B(M), L(M);
	for (int i = 0; i < M; ++i)
		cin >> A[i] >> B[i] >> L[i];

	cout << illumina(N, M, H, A, B, L) << "\n";
}

#endif
