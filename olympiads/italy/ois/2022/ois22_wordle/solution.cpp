#include <iostream>

using namespace std;

int main()
{
	int conta = 0;
	int N;
	cin >> N;
	
	char L[N];
	for(int i = 0; i < N; i++)
	{
		cin >> L[i];
		if(L[i] == '_')
		{
			conta += 1;
		}
	}
	
	int casi = 1;
	for(int i = 0; i < conta; i++)
	{
		casi *= 26 - (N - conta) - i;
	}
	
	cout << casi;

}