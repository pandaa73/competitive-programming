#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
	ifstream cin("input.txt");
	
	int A, B;
	cin >> A >> B;
	
	int a[A], b[B];
	for(int i = 0; i < A; i++)
		cin >> a[i];
	
	for(int i = 0; i < B; i++)
		cin >> b[i];
		
	sort(a, a+A);
	sort(b, b+B);
	
	int i = 0, j = 0, second = 0;
	
	while(i < A and j < B)
	{
		if(a[i] < b[j])
			i++;
		else if(a[i] > b[j])
			j++;
		else
		{
			j++;
			i++;
			second++;
		}
	}
	
	cout << second;
}
