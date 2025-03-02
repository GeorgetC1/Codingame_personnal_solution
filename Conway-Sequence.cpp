#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// fonction de Conway
vector<int> conwayFct(int r, int l)
{
    vector<vector<int>> grid(l);


    // on initialise le compteur et le numéro compté
    int count = 0, number = 0;
    for (int i=0; i<l; i++)
    {
        if(i==0) // ligne de départ i==0
        {
            grid[0].push_back(r);
            continue;
        }

        number = 0;
        count = 0;
        vector<int> line = grid[i-1];
        for( int g = 0; g < line.size(); g++)
        {
            cerr << line[g];
            if(number != line[g])
            {
                if(g != 0)
                {
                    grid[i].push_back(count);
                    grid[i].push_back(number);
                }
                number = line[g];
                count = 1;
            }
            else count ++;
        }

        grid[i].push_back(count);
        grid[i].push_back(number);
    }

    // on retourne la ligne voulue 
    // l-1 car on commence à l'indice 0 et non 1
    return grid[l-1];
}

int main()
{
    int r;
    cin >> r; cin.ignore();
    int l;
    cin >> l; cin.ignore();

    // on récupère la ligne voulue
    vector<int> answer = conwayFct(r,l);

    // on écrit la sortie
    for(int i = 0; i < answer.size(); i++) 
    {
        cout << answer[i];
        if(i < answer.size() - 1) cout << " ";
    }
    cout << endl;
}