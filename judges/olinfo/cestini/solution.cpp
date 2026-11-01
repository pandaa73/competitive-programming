#include <iostream>
#include <map>
#include <vector>

using namespace std;

map <int, vector <int>> cestini;
map <int, int> ogg;

int inizia(int N, int M)
{
	ogg[0] = N;
	for(int i = 0; i < N; i++)
	{
		cestini[0].push_back(i);
	}
	
	return 0;
}

void sposta(int a, int b)
{
	cestini[b].push_back(cestini[a][ogg[a]-1]);
	cestini[a].pop_back();
	ogg[a] -= 1;
	ogg[b] += 1;
}

int controlla(int a, int i)
{
	if(ogg[a] > i)
	{
		return cestini[a][i];
	}
	else
	{
		return -1;	
	}
}