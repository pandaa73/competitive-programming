#include <fstream>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int direziona(int N, vector<int> A, vector<int> B)
{
	int min = INT_MAX;
	int max = 0;
	
	int iA = 0, iB = 0;
	
	while(iB < N)
	{
		if(A[iA] < B[iB])
		{
			iA++;
		}
		
		iB++;
	}
	
	max = iA;
	
	iA = N-1;
	iB = N-1;
	
	while(iB >= 0)
	{
		if(A[iA] > B[iB])
		{
			iA--;
		}
		iB--;
	}
	
	min = iA;
	
	return max - min;
}