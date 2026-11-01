#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	
	int T[N];
	for(int i = 0; i < N; i++)
	{
		cin >> T[i];
	}
	
	int deliveryTime = T[0];
	int reorders = 0;
	
	for(int i = 1; i < N; i++)
	{
		if(T[i]+i < deliveryTime)
		{
			deliveryTime = T[i]+i;
			reorders++;
		}
	}
	
	cout << deliveryTime << " " << reorders;
}