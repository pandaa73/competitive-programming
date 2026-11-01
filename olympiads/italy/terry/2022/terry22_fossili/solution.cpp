#include <bits/stdc++.h>

using namespace std;

struct Fossil {
	int a;
	int b;
};

int main() {
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	
	int T;
	cin >> T;
	
	for(int t = 0; t < T; t++) {
		int startMax = 0, endMin = INT_MAX;
		vector<Fossil> V(3);
		for(int i = 0; i < 3; i++) {
			int a, b;
			cin >> a >> b;
			
			startMax = max(startMax, a);
			endMin = min(endMin, b);
			
			V[i] = (Fossil){a, b};
		}
		
		if(startMax > endMin) {
			cout << "Case #" << t+1 << ": " << -1 << endl;
			continue;
		}
		
		cout << "Case #" << t+1 << ": " << endMin - startMax << endl;
	}
}
