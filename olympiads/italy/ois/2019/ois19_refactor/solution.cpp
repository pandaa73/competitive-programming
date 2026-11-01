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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string S; cin >> S;
    const int N = S.size();

    string T = "", buf;
    while(getline(cin, buf)) {
        T.append(buf);
        T.push_back('\n');
    }

    int M = T.size();

    S.push_back('?');
    for(int p = 0; p < M; ++p) {
        int lstr = T.find('"', p);
        int lmul = T.find("/*", p);
        int lsin = T.find("//", p);

        if(lstr == string::npos) lstr = M;
        if(lmul == string::npos) lmul = M;
        if(lsin == string::npos) lsin = M;

        int l = min({lstr, lmul, lsin});
        S += T.substr(p, l - p);

        if(l == M) break;

        if(l == lstr) {
            p = T.find('"', l + 1);
        } else if(l == lmul) {
            p = T.find("*/", l + 1);
        } else if(l == lsin) {
            p = T.find('\n', l + 1);
        }

        if(p == string::npos) break;
    }

    M = S.size();

    auto is_valid = [&](char c) -> bool {
        return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')
            || ('0' <= c && c <= '9') || (c == '_');
    };

    int l = 0;
    vector<int> z(M);
    for(int i = 1; i < M; ++i) {
        if(i < l + z[l]) {
            z[i] = min(l + z[l] - i, z[i - l]);
        }

        while(i + z[i] < M && S[z[i]] == S[i + z[i]]) z[i] += 1;

        if(i + z[i] > l + z[l]) l = i;
    }

    int cnt = 0;
    for(int i = N; i < M; ++i) {
        if(z[i] < N) continue;

        bool l = (i     == 0) || !is_valid(S[i - 1]);
        bool r = (i + N >= M) || !is_valid(S[i + N]);

        cnt += l&r;
    }

    cout << cnt << lf;
}
