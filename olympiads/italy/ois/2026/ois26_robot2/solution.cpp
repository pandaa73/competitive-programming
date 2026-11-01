#include <bits/stdc++.h>
#include <queue>
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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, K; cin >> N >> M >> K;

    string S; cin >> S;

    if(K == N * M) return cout << 0 << lf, 0;

    vector vis(N, vector<bool>(M));

    priority_queue<int> q;

    q.push(0);
    vis[0][0] = 1;

    int x = 0, y = 0;
    for(int i = 0; i < S.size(); ++i) {
        char c = S[i];

        switch(c) {
            case 'L': y--; break;
            case 'R': y++; break;
            case 'U': x--; break;
            case 'D': x++; break;
        }

        infof("after %d: (%d, %d)", i, x, y);

        if(vis[x][y]) continue;

        vis[x][y] = 1;
        q.push(i);

        infof("... q.push(%d)", i);
    }

    K -= N * M - q.size();

    infof("K on path is %d", K);

    int last = S.size();

    while(K-- > 0) last = q.top(), q.pop();

    cout << last << lf;
}
