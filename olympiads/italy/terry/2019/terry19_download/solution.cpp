#include <bits/stdc++.h>
using namespace std;
// flag[10]

void Solve() {
	int n, f, c; cin >> n >> f >> c;

	int mov = n/f;
	int spc = n-f*mov;
	int sng = spc/c;

	cout << mov << " " << sng; 
}

int main() {
	freopen("territoriali/input.txt", "r", stdin);
	freopen("territoriali/output.txt", "w", stdout);
	
	int t; cin >> t;
	for(int i = 0; i < t; ++i) {
		cout << "Case #" << i+1 << ": ", Solve(), cout << "\n"; 
	}
}
