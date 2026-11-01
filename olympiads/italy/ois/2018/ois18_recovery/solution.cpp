#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdio.h> 
#include <string.h> 
#include <limits.h> // INT_MAX

using namespace std;

int T, S, Q;

vector<string> t_vector;
vector<string> s_vector;

map<string, int> t_map;
map<string, int> s_map;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int i,j, valore;
    
    cin >> T >> S  >> Q;
    
    char * impronta = (char *)malloc(Q+1);
    impronta[Q]=0;  // Terminatore
    
    t_vector.resize(T);
    s_vector.resize(S);
    
    for (i = 0; i<T; i++)
    {
        for (j=0;  j<Q; j++)
        {    
            cin >> valore;  // compreso tra 1 e 32
            impronta[j]= (char)('A' + valore -1);    // traslo il numero in una lettera ... in modo da sfruttare le stringhe 

        }    
        sort( &impronta[0], &impronta[Q]);
        t_vector[i] = impronta;
    }

    for (i = 0; i<S; i++)
    {
        for (j=0;  j<Q; j++)
        {    
            cin >> valore;  // compreso tra 1 e 32
            impronta[j]= (char)('A' + valore -1);    // traslo il numero in una lettera ... in modo da sfruttare le stringhe 
            
        }    
        sort( &impronta[0], &impronta[Q]);
        s_vector[i] = impronta;
    }

    sort(t_vector.begin(), t_vector.end());
    sort(s_vector.begin(), s_vector.end());
    
    t_map[ t_vector[0] ] = 1;
    for (i=1; i<t_vector.size(); i++)
    {
        if (t_vector[i] == t_vector[i-1])
            t_map[ t_vector[i] ] ++;
        else
            t_map[ t_vector[i] ] = 1;
    }
    
    s_map[ s_vector[0] ] = 1;
    for (i=1; i<s_vector.size(); i++)
    {
        if (s_vector[i] == s_vector[i-1])
            s_map[ s_vector[i] ] ++;
        else
            s_map[ s_vector[i] ] = 1;
    }

    map<string, int>::iterator Tit;
    map<string, int>::iterator Sit;
    
    int conta = 0;
    for (Tit = t_map.begin();  Tit != t_map.end(); Tit++)
    {
        string key = Tit->first;
        
        Sit = s_map.find(key);
        if (Sit != s_map.end() )
            conta += Sit->second * Tit->second; 
    }
    cout << conta;
    
    /*
    cout << "//============= TEST ================== \n";
    for (Tit = t_map.begin();  Tit != t_map.end(); Tit++)
    {
        cout <<Tit->first << "  " << Tit->second << "\n";
    }
    cout << "//============= STUDENT ================== \n";
    for (Sit = s_map.begin();  Sit != s_map.end(); Sit++)
    {
        cout <<Sit->first << "  " << Sit->second << "\n";
    }
*/    

}    
