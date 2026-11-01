// NOTE: it is recommended to use this even if you don't understand the
// following code.

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    //  uncomment the following lines if you want to read/write from files
    //  ifstream cin("input.txt");
    //  ofstream cout("output.txt");

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N, Q;
        cin >> N >> Q;
        
        vector<int> P(N), L(Q);
        for (int i = 0; i < N; i++) {
            cin >> P[i];
        }
        for (int i = 0; i < Q; i++) {
            cin >> L[i];
        }


        // insert your code here
        bool hacker = false;
		long long totalMoney = 0;
		for(int i = 0; i < Q; i++)
		{
			if(L[i] > 0)
				totalMoney += L[i];
			else
				totalMoney -= P[-1*L[i]-1];
			
			if(totalMoney < 0)
				hacker = true;
		}

        // print the result
        if (hacker) {
            cout << "HACKER" << endl;
        } else {
            cout << "OK" << endl;
        }
    }
}
