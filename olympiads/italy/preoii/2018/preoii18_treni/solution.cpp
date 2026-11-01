#include <bits/stdc++.h>
using namespace std;
// flag[10]

int tempo_massimo(int n, int a[], int b[]) {
	int dp[n]; dp[0] = max(a[0], b[0]);
	
	for(int i = 1; i < n; ++i) {
		if(i == 1) {
			dp[1] = max(a[1] + dp[0], b[1]);
			continue;
		}
		
		dp[i] = max(a[i] + dp[i-1], b[i] + dp[i-2]);
	}
	
	return dp[n-1];
}