#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	//fstream cin("input.txt");
	
	int N;
	cin >> N;
	
	int S[N], P[N];
	long long sum = 0;
	long long maxSum = 0;
	for(int i = 0; i < N; i++)
	{
		cin >> S[i] >> P[i];
		sum += S[i], maxSum += P[i];
	}
	
	long long bestSum = sum;
	long long bestMaxSum = maxSum;
	long long discard;
	for(int i = 0; i < N; i++)
	{
		sum -= S[i], maxSum -= P[i];
		if(bestSum*maxSum <= sum*bestMaxSum)
		{
			bestSum = sum;
			bestMaxSum = maxSum;
			discard = i;
		}
		
		sum += S[i], maxSum += P[i];
	}
	
	
	cout << discard << endl;
}