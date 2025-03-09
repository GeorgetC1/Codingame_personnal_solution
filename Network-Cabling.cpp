#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

using Point = pair<long,long>;


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

long calculLongueurCable(long minX, long maxX, const vector<Point>& listOfPoints) 
{
    // Calcul de la médiane
    vector<long> values;
    for (const auto& p : listOfPoints) {
        values.push_back(p.second);
    }
    
    // Trier le vecteur pour trouver la médiane
    sort(values.begin(), values.end());
    long mediane;
    if (values.size() % 2 == 0) {
        mediane = (values[values.size()/2 - 1] + values[values.size()/2]) / 2;
    } else {
        mediane = values[values.size()/2];
    }

    long somme = abs(maxX-minX); // longueur de la mediane , depuis le point le plus à gauche au point le plus à droite
    // + la distance de chaque point à la médiane
    for (int i=0; i<listOfPoints.size(); i++)
    {
        somme += abs(listOfPoints.at(i).second - mediane);
    }

    return somme;
}

int main()
{
    int n;
    cin >> n; cin.ignore();
    long minX = numeric_limits<long>::max(), 
            maxX = numeric_limits<long>::min(), 
            minY = numeric_limits<long>::max(), 
            maxY = numeric_limits<long>::min();

    vector<Point> listOfPoints; 
    for (int i = 0; i < n; i++) {
        long x;
        long y;
        cin >> x >> y; cin.ignore();

        listOfPoints.push_back({x,y});

        if(maxX <= x) maxX = x;
        if(minX >= x) minX = x;
        if(maxY <= y) maxY = y;
        if(minY >= y) minY = y;
    }

    cout << calculLongueurCable(minX, maxX, listOfPoints) << endl;
}