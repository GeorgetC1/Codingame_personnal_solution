#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


void moveToPos(const int w, const int h,vector<vector<char>>& map, char letter, int pos) 
{
    int finalH = 0;

    // Parcours vertical pour trouver la position finale
    for(int i=0; i < h; i++)
    {
        if(map[pos][i] == ' ') finalH=i;
        else
        {
            // Pour les lettres majuscules, priorité gauche puis droite
            if(isupper(letter))
            {
                if(pos > 1 && map[pos-1][i] == ' ') 
                {
                    finalH = i; 
                    pos--;
                }
                else if(pos < w && map[pos+1][i] == ' ') 
                {
                    finalH = i; pos++;
                }
            } 
            // Pour les lettres minuscules, priorité droite puis gauche
            else if(islower(letter))
            {
                if(pos < w && map[pos+1][i] == ' ') 
                {
                    finalH = i; 
                    pos++;
                }
                else if(pos > 1 && map[pos-1][i] == ' ') 
                {
                    finalH = i; 
                    pos--;
                }   
            }
        } 
    }
    map[pos][finalH] = letter;
}

int main()
{
    int w;
    int h;
    cin >> w >> h; cin.ignore();
    int n;
    cin >> n; cin.ignore();

    // taille de la grille totale
    // on crée la grille avec les bords
    int width = w+2, height = h+1;
    vector<vector<char>> grid(width, vector<char>(height,' '));

    // on lit les lettres et leurs positions
    for (int i = 0; i < n; i++) {
        char l;
        int p;
        cin >> l >> p; cin.ignore();

        // on déplace la lettre à la position p+1 car il y a un bord à gauche
        moveToPos(w,h,grid, l, p+1);
    }

    // on ajoute les bords à droite et à gauche
    for (int i = 0; i < height; i++)
    {
        grid[0][i] = '|';
        grid[width-1][i] = '|';
    }

    // on ajoute les bords en bas    
    for (int i=0; i<width; i++)
    {
        grid[i][h] =(i == 0 || i == width-1) ? '+' : '-';
    }
    
    // on sort le résultat
    for(int y = 0; y<height; y++)
    {
        for(int x = 0; x<width; x++)
        {
            cout << grid[x][y];
        }
        cout << endl;
    }    
}