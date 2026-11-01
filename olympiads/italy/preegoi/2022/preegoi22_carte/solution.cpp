#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int scarta(int C, vector<bool> L, vector<bool> D, vector<bool> N)
{
	int avanzate = 0;
	int qual;
	
	for(int i = 0; i < C; i++)
	{
		qual = 0;
		if(L[i])
		{
			qual += 1;
		}
		if(D[i])
		{
			qual += 1;
		}
		if(N[i])
		{
			qual += 1;
		}
		if(qual != 1) 
		{
			avanzate += 1;
		}
		//cout << "i = " << i << endl << "qual = " << qual << endl << "avanzate = " << avanzate << endl;
	}
	
	return avanzate;
}