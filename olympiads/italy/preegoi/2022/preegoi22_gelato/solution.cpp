#include <vector>
#include <algorithm>

using namespace std;

int presta(int N, int C, vector<int> P)
{
	int minAmici = 0;
	int costo = 0;
	
	sort(P.rbegin(), P.rend());

	while(costo < C)
	{
		costo += P[minAmici];
		minAmici++;
	}
	
	return minAmici;
}
