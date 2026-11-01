#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	
	float somma = 0;     
	int N;
	cin >> N;
	
	int V[N];
	for(int i = 0; i < N; i++)
	{
		cin >> V[i];
		somma += V[i];
	}

	float media = somma / N;
	cout << somma << " " << media;
}