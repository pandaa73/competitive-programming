#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5+1;
vector<int> adj[N];

void dfs(int u, int w, int& x) {
	x += w; ++w;
	for(auto v: adj[u]) dfs(v, w, x);
}

int coppie(int n, int c[]) {
	int src;
	for(int i = 0; i < n; ++i) {
		if(c[i] == -1) {
			src = i; continue;
		}
		
		adj[c[i]].push_back(i);
	}
	
	int x = 0; dfs(src, 0, x);
	return x;
}
