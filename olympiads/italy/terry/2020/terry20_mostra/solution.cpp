#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;

	for(int t = 0; t < T; t++) {
		int N, M;
		cin >> N >> M;

		vector<int> V(N+1, 0), G(M+1, 0);
		for(int v = 1; v <= N; v++) cin >> V[v];
		for(int g = 1; g <= M; g++) cin >> G[g];

		vector<vector<int>> dp(N+1, vector<int>(M+1, 0));
		for(int i = 1; i <= N; i++) {
			int v = V[i];

			for(int j = 0; j <= M; j++) {
				int g = G[j];

				if(j == 0) {
					dp[i][j] = dp[i-1][j] + 1;
					continue;
				}

				if(g > v) {
					dp[i][j] = max(max(dp[i][j-1], dp[i-1][j-1] + 2), dp[i-1][j] + 1);
					continue;
				}

				dp[i][j] = max(max(dp[i][j-1], dp[i-1][j-1] + 1), dp[i-1][j] + 1);
			}
		}

		cout << "Case #" << t+1 << ": " << dp[N][M] << endl;
	}
}
