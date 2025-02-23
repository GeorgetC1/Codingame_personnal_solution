#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

vector<pair<int, int>> findPath(const int &rows, const int &cols, vector<string> &grid, const pair<int, int> &start, const char &goal)
{
    auto dist = vector<vector<int>>(rows, vector<int>(cols, numeric_limits<int>::max()));                                                      // matrice (x,y,dist)
    auto prevP = vector<vector<pair<int, int>>>(rows, vector<pair<int, int>>(cols, {numeric_limits<int>::max(), numeric_limits<int>::max()})); // vector of {x,y} with {x0,y0} has index
    vector<pair<int, int>> notVisitedPoint;

    dist[start.first][start.second] = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            notVisitedPoint.push_back({i, j});
        }
    }

    while (!notVisitedPoint.empty())
    {
        vector<pair<int, int>>::iterator itMin = notVisitedPoint.begin();
        int minValue = numeric_limits<int>::max();
        for (auto it = notVisitedPoint.begin(); it < notVisitedPoint.end(); it++)
        {
            if (dist[it->first][it->second] < minValue)
            {
                minValue = dist[it->first][it->second];
                itMin = it;
            }
        }

        if (minValue == numeric_limits<int>::max())
            return {};

        pair<int, int> target = *itMin;
        notVisitedPoint.erase(itMin); // point visited

        // we have reached to goal !
        if (grid[target.first][target.second] == goal)
        {

            vector<pair<int, int>> path;
            pair<int, int> curr = target;

            while (prevP[curr.first][curr.second].first != numeric_limits<int>::max())
            {
                path.push_back(curr);
                curr = prevP[curr.first][curr.second];
            }

            if (path.empty())
                return {};
            else
                return path;
        }

        if (grid[target.first][target.second] != '?') // useless for ?
        {
            // check neighbors
            vector<pair<int, int>> neighbors;
            if (grid[target.first][target.second + 1] != '#') // RIGHT
            {
                neighbors.push_back({target.first, target.second + 1});
            }
            if (grid[target.first][target.second - 1] != '#') // LEFT
            {
                neighbors.push_back({target.first, target.second - 1});
            }
            if (grid[target.first + 1][target.second] != '#') // DOWN
            {
                neighbors.push_back({target.first + 1, target.second});
            }
            if (grid[target.first - 1][target.second] != '#') // UP
            {
                neighbors.push_back({target.first - 1, target.second});
            }

            // check each neighbors and update the distances
            for (const auto &n : neighbors)
            {
                int d = dist[target.first][target.second] + 1; // cost 1
                if (d < dist[n.first][n.second])
                {
                    dist[n.first][n.second] = d;
                    prevP[n.first][n.second] = target;
                }
            }
        }
    }
    return {};
}

int main()
{
    int r; // number of rows.
    int c; // number of columns.
    int a; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    cin >> r >> c >> a;
    cin.ignore();

    bool cReached = false, commandFound = false;
    // game loop
    while (1)
    {
        vector<string> mapTot;
        int kr; // row where Rick is located.
        int kc; // column where Rick is located.
        cin >> kr >> kc;
        cin.ignore();
        for (int i = 0; i < r; i++)
        {
            string row;
            cin >> row;
            cin.ignore();

            size_t found = row.find('C');
            if (found != string::npos)
                commandFound = true;

            mapTot.push_back(row);
        }

        if (mapTot[kr][kc] == 'C')
            cReached = true;

        vector<pair<int, int>> path;
        if (cReached)
            path = findPath(r, c, mapTot, {kr, kc}, 'T');
        else
        {
            if (commandFound)
                path = findPath(r, c, mapTot, {kr, kc}, 'C');

            if (path.empty())
                path = findPath(r, c, mapTot, {kr, kc}, '?');
        }

        pair<int, int> goal = path.back();
        if (goal.second > kc)
            cout << "RIGHT" << endl;
        else if (goal.second < kc)
            cout << "LEFT" << endl;
        else if (goal.first > kr)
            cout << "DOWN" << endl;
        else if (goal.first < kr)
            cout << "UP" << endl;
    }
}