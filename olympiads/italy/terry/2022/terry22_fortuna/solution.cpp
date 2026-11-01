#include <bits/stdc++.h>

using namespace std;

void Turn(vector<int>& V) {
	int tmp = V[V.size()-1];
	
	for(int i = V.size()-1; i > 0; i--) {
		V[i] = V[i-1];
	}
	
	V[0] = tmp;
}

int main() {
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	
	int T;
	cin >> T;
	
	for(int t = 0; t < T; t++) {
		int N;
		cin >> N;
		
		vector<int> V(N), G(N);
		for(int& x: V) cin >> x;
		for(int& x: G) cin >> x;
		
		int Min = INT_MAX;
		for(int i = 0; i < N; i++) {
			int cost = 0;
			
			for(int j = 0; j < N; j++) cost += V[j]*G[j];
			Min = min(Min, cost);
			
			Turn(V);
		}
		
		cout << "Case #" << t+1 << ": " << Min << endl;
	}
}
