// @check-accepted: examples same_side quadratic no_limits
#include <string>
using namespace std;

int ribalta(int N, string S) {
    int total = 0;
    for(auto c: S) total += c - '0';

    int cnt = 0, mx = total;
    for(int i = 0; i < N; ++i) {
        cnt += S[i] - '0';

        mx = max(mx, total + i + 1 - 2 * cnt);
    };

    return mx;
}
