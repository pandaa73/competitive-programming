#include <vector>

using namespace std;

pair<int, vector<int>> raccogli(int N, int K, vector<int> A) {
    vector<int> dp(N + 1);
    vector<int> last(N + 1);
    for(int i = 1; i <= N; ++i) {
        int x = A[i - 1] + (i >= K ? dp[i - K] : 0);
        if(x > dp[i - 1]) {
            dp[i] = x;
            last[i] = i;
        } else {
            dp[i] = dp[i - 1];
            last[i] = last[i - 1];
        }
    }

    vector<int> taken;
    for(int n = N; n > 0; n -= K) {
        n = last[n];
        if(n > 0) taken.emplace_back(n - 1);
    }

    return {dp[N], taken};
}
