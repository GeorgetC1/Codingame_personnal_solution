#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

// mon object escargot
class Snail {
    private :
        int _num;
        pair<int,int> _pos;
        double _speed;
    
    public:
    Snail (): _num(0), _speed(0) {};
    Snail (int num, pair<int,int> pos, double speed): _num(num), _pos(pos), _speed(speed) {};

    int getNum() const { return _num;}
    int getX() const { return _pos.first;};
    int getY() const { return _pos.second;};
    double getSpeed() const { return _speed;}

    void setPos( pair<int,int> pos) { _pos = pos; };
};

int main()
{
    int nbSnail;
    cin >> nbSnail; cin.ignore();

    vector<Snail>  snails(nbSnail); // liste d'escargot

    // récupération des vitesses des escargots
    for (int i = 0; i < nbSnail; i++) {
        double speedSnail;
        cin >> speedSnail; cin.ignore();

        snails[i] = Snail(i+1, {0,0}, speedSnail);
    }

    int mapH; cin >> mapH; cin.ignore();
    int mapW; cin >> mapW; cin.ignore();

    // la grid
    vector<string> map(mapH);
    for ( auto& line : map ) { getline(cin, line); cerr << line << endl;}

    // listons les sorties et la position des escargots
    vector<pair<int,int>> sorties;
    for (int i=0; i < mapH; i++)
    {
        for(int j=0; j < mapW; j++)
        {
            switch (map[i][j])
            {
                case '*' : break;
                case '#' : 
                    sorties.push_back({i,j});
                    break;
                default :
                    snails[(map[i][j]-'0')-1].setPos({i,j});
                    break;
            }
        }
    }

    int res = -1, distance = numeric_limits<int>::max();
    for (const auto& snail : snails)
    {
        
        if (snail.getSpeed() == 0) continue;
        for( const auto& sortie : sorties)
        {
            int distX = abs(sortie.first - snail.getX());
            int distY = abs(sortie.second - snail.getY());

            double currDist = ceil((distX+distY)/snail.getSpeed());
            
            if ( distance > currDist)
            {        
                res = snail.getNum();
                distance = currDist;
            }
        }
    }

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << res << endl;
}