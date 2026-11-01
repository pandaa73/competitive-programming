#include <bits/stdc++.h>
using namespace std;
// flag[10]

void Solve() {
	int k; cin >> k;
	array<int, 4> v; for(int& x: v) cin >> x;
 
	int mx = v[0]+2*v[1]+3*v[2]+4*v[3];
	for(int i = 0; i < 3; ++i) {
		if(k <= v[i]) {
			mx += (3-i)*k; break;
		}
			
		k -= v[i];
		mx += (3-i)*v[i];
	}

    cout << mx;
}

int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);

    int t; cin >> t;
    for(int i = 1; i <= t; ++i) cout << "Case #" << i << ": ", Solve(), cout << endl;
}