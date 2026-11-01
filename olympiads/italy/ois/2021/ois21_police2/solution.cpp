#include <iostream>
#include <fstream>

using namespace std;

int main()
{	
	ifstream cin("input.txt");
	
	int N;
	cin >> N;
	
	int V[N];
	for(int i = 0; i < N; i++)
		cin >> V[i];
	
	int visLoop[N];
	bool visited[N];
	for(int i = 0; i < N; i++)
		visited[i] = false;
		
	for(int i=0; i<N; i++)
		visLoop[i] = -1;
	
	int loop = 0;
	
	for(int i = 0; i < N; i++)
	{
		if(visited[i])
			continue;
		
		bool skip = false;
		
		int house = i;
		int j = 0;
		visLoop[house] = j;
		
		while(visLoop[V[house]] == -1)
		{
			if(visited[house])
			{
				skip = true;
				break;		
						
			}

			
			j++;
			house = V[house];
			visLoop[house] = j;
		}
		
		if(skip)
			continue;
		
		loop = max(loop, visLoop[house] - visLoop[V[house]] + 1);
		
		house = i;
		
		while(visLoop[house] != -1)
		{
			visLoop[house] = -1;
			visited[house] = true;	
			
			house = V[house];
		}
		
	}
	
	cout << loop;
}
