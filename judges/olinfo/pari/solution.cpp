#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	
	int N;
	cin >> N;
	
	if(N %2 == 0)
	{
		cout << "pari";
	}
	else
	{
		cout << "dispari";
	}

}