#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infor(str, ...) do { fprintf(stderr, str, __VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infor
#undef infof

#define infos(str)
#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int N;
vector<string> M;

vector<vector<int>> pfx_a;
vector<vector<int>> pfx_b;

void init(int N, vector<string> M) {
    ::N = N;
    ::M = M;

    pfx_a.resize(2 * N + 1);
    for(auto &v: pfx_a) v.resize(N + 1);

    pfx_b.resize(2 * N + 1);
    for(auto &v: pfx_b) v.resize(N + 1);

    for(int d = 0; d < 2 * N + 1; ++d) {
        infof("----- d = %d -----", d);

        for(int x = 0; x < N; ++x) {
            int y = x - (d - N);

            if(y < 0 || y >= N) continue;

            infof("A: (%d, %d, %d): %c", d, x, y, M[x][y]);

            pfx_a[d][x + 1] = pfx_a[d][x] + (M[x][y] == '1');
        }

        for(auto x: pfx_a[d])
            infor("%d ", x);
        infos("");
        infos("");

        for(int x = 0; x < N; ++x) {
            int y = d - x;

            if(y < 0 || y >= N) continue;

            infof("B: (%d, %d, %d): %c", d, x, y, M[x][y]);

            pfx_b[d][x + 1] = pfx_b[d][x] + (M[x][y] == '1');
        }

        for(auto x: pfx_b[d])
            infor("%d ", x);
        infos("");
    }
}

bool query(int h, int x, int y) {
    int sz = h + 1;

    bool ok = 1;

    assert(N > 1);
    if(sz == 2) {
        ok &= M[x][y] == M[x + 1][y + 1];
        ok &= M[x][y] != M[x][y + 1];
        ok &= M[x][y] != M[x + 1][y];

        return ok;
    }

    int d = x - y + N;
    int k = pfx_a[d][x + sz] - pfx_a[d][x];

    bool b = k == 0;

    infos("-------------");
    infof("query(%d, %d, %d):", h, x, y);
    infof("d_a = %d | d_b = %d | sz = %d", d, x + y + sz - 1, sz);

    infos("");
    infos("A:");
    infof("-2: %d", pfx_a[d - 2][x + sz - 2] - pfx_a[d - 2][x]);
    infof("-1: %d", pfx_a[d - 1][x + sz - 1] - pfx_a[d - 1][x]);
    infof(" 0: %d", pfx_a[d + 0][x + sz] - pfx_a[d + 0][x + 0]);
    infof("+1: %d", pfx_a[d + 1][x + sz] - pfx_a[d + 1][x + 1]);
    infof("+2: %d", pfx_a[d + 2][x + sz] - pfx_a[d + 2][x + 2]);

    if(b) {
        ok &= pfx_a[d - 2][x + sz - 2] - pfx_a[d - 2][x] == sz - 2;
        ok &= pfx_a[d - 1][x + sz - 1] - pfx_a[d - 1][x] == sz - 1;
        ok &= k == 0;
        ok &= pfx_a[d + 1][x + sz] - pfx_a[d + 1][x + 1] == sz - 1;
        ok &= pfx_a[d + 2][x + sz] - pfx_a[d + 2][x + 2] == sz - 2;
    } else {
        ok &= pfx_a[d - 2][x + sz - 2] - pfx_a[d - 2][x] == 0;
        ok &= pfx_a[d - 1][x + sz - 1] - pfx_a[d - 1][x] == 0;
        ok &= k == sz;
        ok &= pfx_a[d + 1][x + sz] - pfx_a[d + 1][x + 1] == 0;
        ok &= pfx_a[d + 2][x + sz] - pfx_a[d + 2][x + 2] == 0;
    }

    if(ok) return 1;

    ok = 1;

    d = x + y + sz - 1;
    k = pfx_b[d][x + sz] - pfx_b[d][x];

    b = k == 0;

    infos("");
    infos("B:");
    infof("-2: %d", pfx_b[d - 2][x + sz - 2] - pfx_b[d - 2][x]);
    infof("-1: %d", pfx_b[d - 1][x + sz - 1] - pfx_b[d - 1][x]);
    infof(" 0: %d", pfx_b[d + 0][x + sz] - pfx_b[d + 0][x + 0]);
    infof("+1: %d", pfx_b[d + 1][x + sz] - pfx_b[d + 1][x + 1]);
    infof("+2: %d", pfx_b[d + 2][x + sz] - pfx_b[d + 2][x + 2]);

    if(b) {
        ok &= pfx_b[d - 2][x + sz - 2] - pfx_b[d - 2][x] == sz - 2;
        ok &= pfx_b[d - 1][x + sz - 1] - pfx_b[d - 1][x] == sz - 1;
        ok &= k == 0;
        ok &= pfx_b[d + 1][x + sz] - pfx_b[d + 1][x + 1] == sz - 1;
        ok &= pfx_b[d + 2][x + sz] - pfx_b[d + 2][x + 2] == sz - 2;
    } else {
        ok &= pfx_b[d - 2][x + sz - 2] - pfx_b[d - 2][x] == 0;
        ok &= pfx_b[d - 1][x + sz - 1] - pfx_b[d - 1][x] == 0;
        ok &= k == sz;
        ok &= pfx_b[d + 1][x + sz] - pfx_b[d + 1][x + 1] == 0;
        ok &= pfx_b[d + 2][x + sz] - pfx_b[d + 2][x + 2] == 0;
    }

    return ok;
}

#ifndef EVAL

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<string> M(N);
    for (int i = 0; i < N; i++)
        cin >> M[i];

    init(N, M);

    for (int i = 0; i < Q; i++) {
        int h, x, y;
        cin >> h >> x >> y;
        cout << query(h, x, y) << '\n';
    }
}

#endif
