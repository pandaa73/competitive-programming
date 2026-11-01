#include <bits/stdc++.h>

using namespace std;

int main() {
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	
	int T;
	cin >> T;
	
	for(int t = 0; t < T; t++) {
		int N;
		cin >> N;
		
		string S;
		cin >> S;
		
		S += "0";
		
		vector<int> C;
		
		int type = S[0]-'0';
		int start = 1-type;
		int count = 1;
		for(int i = 0; i < N-1; i++) {			
			if(S[i+1]-'0' != type) {
				C.push_back(count);
				count = 1;
				type = 1-type;
				continue;
			}
			
			count++;
		}
		
		C.push_back(count);
		
		if(C[0] == N) {
			start = 1-start;
			cout << "Case #" << t+1 << ": " << N*start + (1-start) << endl;
			continue;
		}
		
		C.push_back(0);
		C.push_back(0);
		
		int maxN = 0;
		for(int i = start; i < C.size()-2; i+=2) {
			if(C[i+1] == 1) {
				maxN = max(maxN, C[i]+1+C[i+2]);
				continue;
			}
			
			maxN = max(maxN, C[i]+1);
		}
		
		cout << "Case #" << t+1 << ": " << maxN << endl;
	}
}
