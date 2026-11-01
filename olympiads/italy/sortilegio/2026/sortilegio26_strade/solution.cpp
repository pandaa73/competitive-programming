#include <vector>

using namespace std;

int desospettisciti(int N, int M, int K, vector<int> A, vector<int> B) {
    vector<vector<int>> adj(N), radj(N);
    for(int e = 0; e < M; ++e) {
        adj[A[e]].emplace_back(B[e]);
        radj[B[e]].emplace_back(A[e]);
    }

    vector d(N, vector<int>(3, K + 1));

    const int MAXQ = 4;
    const int MAXD = min(6 * N + 7, K + 1);
    vector<vector<pair<int, int>>> q(MAXQ);

    d[0][0] = 0;
    q[0].emplace_back(0, 0);

    for(int l = 0; l < MAXD; ++l) {
        const int m = l % MAXQ;
        for(int p = 0; p < q[m].size(); ++p) {
            auto [u, k] = q[m][p];

            if(d[u][k] < l) continue;
            if(u == N - 1) return l;

            for(auto v: adj[u]) {
                if(l < d[v][0]) {
                    d[v][0] = l;
                    q[m].emplace_back(v, 0);
                }
            }

            if(k++ > 2) continue;

            for(auto v: radj[u]) {
                if(l + k < d[v][k]) {
                    d[v][k] = l + k;
                    q[(m + k) % MAXQ].emplace_back(v, k);
                }
            }
        }

        q[m].clear();
    }

    return -1;
}
