#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

enum walls
{
    DOWN = 1,  // 0001
    LEFT = 2,  // 0010
    TOP = 4,   // 0100
    RIGHT = 8, // 1000
    MAXVALUE = 15,
};

// using dijkstra
vector<pair<int, int>> findPath(const int &rows, const int &cols, vector<vector<int>> &grid, const pair<int, int> &start, const pair<int, int> &goal)
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
        if (target.first == goal.first && target.second == goal.second)
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

        // check neighbors
        vector<pair<int, int>> neighbors;
        int wallsAround = grid[target.first][target.second];
        if (!(wallsAround & RIGHT)) // RIGHT
        {
            neighbors.push_back({target.first, target.second + 1});
        }
        if (!(wallsAround & LEFT)) // LEFT
        {
            neighbors.push_back({target.first, target.second - 1});
        }
        if (!(wallsAround & DOWN)) // DOWN
        {
            neighbors.push_back({target.first + 1, target.second});
        }
        if (!(wallsAround & TOP)) // UP
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
    return {};
}

int convertCharToInt(const char &value)
{
    int decimalValue = stoi(string(1, value), 0, 16);
    return decimalValue;
}

int main()
{
    int xs;
    int ys;
    cin >> xs >> ys;
    cin.ignore();
    pair<int, int> start = make_pair(ys, xs);

    int xr;
    int yr;
    cin >> xr >> yr;
    cin.ignore();
    pair<int, int> target = make_pair(yr, xr);

    int w;
    int h;
    cin >> w >> h;
    cin.ignore();

    vector<vector<int>> grid(h);
    for (int i = 0; i < h; i++)
    {
        string l;
        cin >> l;
        cin.ignore();
        for (auto c : l)
        {
            grid[i].push_back(convertCharToInt(c));
        }
    }

    vector<pair<int, int>> pathToGo = findPath(h, w, grid, start, target);
    vector<pair<int, int>> pathToComeBack = findPath(h, w, grid, target, start);

    cout << pathToGo.size() << " " << pathToComeBack.size() << endl;
}