#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 2e5+3;
vector<array<int, 3>> adj[N];
ll val[N]; int vis[N];

int dfs(int v, int k) {
	int ans = 0; vis[v] = 1;
	for(auto [u, w, j]: adj[v]) {
		if(j >= k) continue;
		if(!vis[u]) val[u] = val[v]-w, ans |= dfs(u, k);
		else if(val[v]-w != val[u]) return 1;
	} return ans;
}

int main() {
	int n, m; cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({b, c, i});
		adj[b].push_back({a, -c, i});
	}

	int l = 1, r = m+1;
	while(r-l > 1) {
		fill(vis, vis+n, 0);
		int md = (l+r)/2;
		int cmp = 0;
		for(int i = 0; i < n; ++i)
			if(!vis[i]) cmp |= dfs(i, md);

		if(cmp) r = md;
		else l = md;
	} cout << l;
}
