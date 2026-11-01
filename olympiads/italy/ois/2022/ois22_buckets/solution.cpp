#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int N;
	cin >> N;
	
	int D[N];
	for(int i = 0; i < N; i++)
	{
		cin >> D[i];
	}
	
	sort(D, D+N);
	
	bool possible = true;
	for(int i = 0; i < N-1; i++)
	{
		int tmp = D[i];
		if(tmp == D[i+1])
		{
			possible = false;
		}
	}
	if(possible)
	{
		cout << "Ok";
	}
	else
	{
		cout << "Impossible";
	}
}