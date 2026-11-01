#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	
	int J[N];
	for(int i = 0; i < N; i++)
	{
		cin >> J[i];
	}
	

	for(int i = 1; i <= 6; i++)
	{
		int count = 0;
		int casella = 0;
		for(int j = 0; j < N; j++)
		{
			count += 1;
			casella += i;
			while(J[casella] > 0 && casella < N)
			{
				casella += J[casella];	
			}			
			if(casella >= N)
			{
				break;
			}
		}
		cout << count << " ";
	}
	
	
}