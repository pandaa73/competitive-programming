// NOTE: it is recommended to use this even if you don't understand the following code.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	// uncomment the following lines if you want to read/write from files
	// ifstream cin("input.txt");
	// ofstream cout("output.txt");

    int N;
    cin >> N;

    vector<long long> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }

    sort(S.begin(), S.end());
	
	long long somma = 1;
	long long lastNum = S[0];
	long long caramelle = 1;
	for(int i = 1; i < N; i++)
	{
		if(S[i] == lastNum)
		{
			somma += caramelle;
		}
		else
		{
			caramelle++;
			somma += caramelle;
			lastNum = S[i];
		}
	}
	
	cout << somma << endl;
    return 0;
}
