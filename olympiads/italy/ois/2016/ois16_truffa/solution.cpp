#include <bits/stdc++.h>
using namespace std;
// flag[10]

int solve(int n, int v[]) {
	sort(v, v+n);
	int ans = 0;
	
	int sum = 0;
	for(int i = 0; i < n; ++i) {
		sum += v[i];
	}
	
	while(sum <= 0) {
		sum += 2*abs(v[ans]);
	 	ans++;
	}
	
	return ans;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n; cin >> n;
	
	int v[n];
	for(auto& x: v) cin >> x;

	cout << solve(n, v);
}