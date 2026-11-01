#include <bits/stdc++.h>
#include <memory>
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

int get_speed(char c) {
    switch(c) {
        case 'D': return 9;
        case 'U': return -11;
        case 'B': return 10;
    }

    return 0;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    string S; cin >> S;

    int s = 0;
    int ans = 0;
    int cnt = 0;
    for(int i = 0; i < N; ++i) {
        cnt += S[i] == 'H';

        s += get_speed(S[i]);

        while(cnt > 0 && s <= 0) {
            cnt--;
            ans++;
            s += 10;
        }

        if(s <= 0)
            return cout << -1 << lf, 0;
    }

    cout << ans << lf;
}
