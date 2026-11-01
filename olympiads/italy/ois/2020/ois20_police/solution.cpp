#include <iostream>
#include <fstream>

//#include "input.cpp"

using namespace std;

void input(int N);

int main()
{
	//input(3);
	
	ifstream cin("input.txt");
	
	int N;
	cin >> N;
	
	int K;
	cin >> K;
	
	int V[N];
	for(int i = 0; i < N; i++)
	{
		cin >> V[i];
	} 
	
	bool visited[N];
	for(int i = 0; i < N; i++)
	{
		visited[i] = false;
	}
	
	int house = 1;
	int attempts = 0; 
		
	while(house != K)
	{
		if(visited[house - 1])
		{
			attempts = -1;
			break;
		}
		
		visited[house - 1] = true;
		
		house = V[house - 1];
		
		attempts++;
	}
	
	cout << attempts;
}
