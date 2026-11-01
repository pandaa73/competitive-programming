#include <iostream>

using namespace std;

int main()
{
	bool isWinnable = true;
	
	int N;
	cin >> N;
	
	int A[N];
	int B[N];
	for(int i = 0; i < N; i++)
	{
		cin >> A[i] >> B[i];
	}
	
	for(int i = 0; i < N-1; i++)
	{
		if(A[i] > B[i+1] or B[i] < A[i+1])
		{
			isWinnable = false;
			break;
		}
	}
	
	if(isWinnable)
		cout << "YES";
	else
		cout << "NO";
	
}
