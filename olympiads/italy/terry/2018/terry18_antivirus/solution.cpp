#include <bits/stdc++.h>
using namespace std;
// flag[10]

void Solve() {
	vector<int> v(4);
		for(int& x: v) cin >> x;

		int virus;
		cin >> virus;

		vector<string> s(4);
		for(string& x: s) cin >> x;

		string x;
		x.resize(virus);

		vector<int> pos(4);
		for(int j = 0; j <= v[0] - virus; j++) {	
			for(int k = 0; k < virus; k++) {
				x[k] = s[0][k+j];
			}
			
			pos[0] = j;
			pos[1] = s[1].find(x);
			pos[2] = s[2].find(x);
			pos[3] = s[3].find(x);

			if(pos[1] != -1 && pos[2] != -1 && pos[3] != -1) {
				cout <<pos[0] << " " << pos[1] << " " << pos[2] << " " << pos[3];
				break;
			}
		}
}

int main() {
	freopen("territoriali/input.txt", "r", stdin);
    freopen("territoriali/output.txt", "w", stdout);
	
	int t; cin >> t;
	for(int i = 0; i < t; i++) { cout << "Case #" << i+1 << ": ", Solve(), cout << "\n"; }
}
