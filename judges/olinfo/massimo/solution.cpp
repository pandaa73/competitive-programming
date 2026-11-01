#include <bits/stdc++.h>
using namespace std;
// flag[10]

int trova_massimo(int n, vector<int> v) {
	int mx = v[0];
	for(int i = 0; i < n; ++i) {
		mx = max(v[i], mx);
	} return mx;
}