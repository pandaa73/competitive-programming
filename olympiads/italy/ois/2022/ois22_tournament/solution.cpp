#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	
	int interesting = 0; //(S[x] - S[y]) + (x - y)
	
	int S[N];
	for(int i = 0; i < N; i++)
	{
		cin >> S[i];
	}
	
	int maxS = S[0];
	int minS = S[0];
	int maxD = S[0];
	int minD = S[0];
	int somma[N];
	int differenza[N];
	
	for(int i = 0; i < N; i++)
	{
		somma[i] = S[i] + i;
		differenza[i] = S[i] - i;
		if(somma[i] > maxS)
		{
			maxS = somma[i];
		}
		if(somma[i] < minS)
		{
			minS = somma[i];
		}
		if(differenza[i] > maxD)
		{
			maxD = differenza[i];
		}
		if(differenza[i] < minD)
		{
			minD = differenza[i];
		}
	}	
	
	int fS = maxS - minS;
	int fD = maxD - minD;
	
	if(fS > fD)
	{
		interesting = fS;
	}
	else
	{
		interesting = fD;
	}
	
	cout << interesting;
}