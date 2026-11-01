#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

#define MAXN 200005

int x[MAXN], y[MAXN];
bool xCheck[MAXN], yCheck[MAXN];

map<pair<int,int>, int> mp;

int main()
{
	ifstream cin("input.txt");
	
	int N;
	cin >> N;

	int X[N], Y[N];
	for(int i = 0; i < N; i++)
	{
		cin >> X[i] >> Y[i];
		mp[{X[i], Y[i]}]++;
	}
		
	for(int i = 0; i < N; i++)
	{
		x[X[i]]++;
		y[Y[i]]++;
	}
	
	long long constellation = 0;
	
	for(int i = 0; i < N; i++)
	{
		int a = x[X[i]] - 1;
		int b = y[Y[i]] - 1;
		
		constellation += a * b;
	}
	
	
	cout << constellation;
}
