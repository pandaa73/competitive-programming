#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream cin("input.txt");
	
	int N;
	cin >> N;
	
	int P[N];
	for(int i = 0; i < N; i++)
	{
		cin >> P[i];
	}
	
	int D = P[0];
	int half = (P[N-1] + P[0]) / 2;
	
	for(int i = 1; i < N; i++)
	{
		if(abs(half-D) > abs(half-P[i]))
			D = P[i];
		else
			break;
	}
	
	if(abs(D - P[0]) > P[N-1] - D)
		D = D - P[0];
	else
		D = P[N-1] - D;
	
	cout << D;
}
