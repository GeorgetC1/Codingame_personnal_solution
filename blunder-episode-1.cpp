#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Robot
{
    private :
        int x;
        int y;
        vector<string> grid;
        string output;
        string lastMove;
        bool modeReverse;
        bool modeBreaker;
        vector<pair<int,int>> teleports;

        struct State {
            int x, y;
            bool modeReverse, modeBreaker;
            string lastMove;
            char currentTerrain;
            
            bool operator==(const State& other) const {
                return x == other.x && 
                       y == other.y && 
                       modeReverse == other.modeReverse &&
                       modeBreaker == other.modeBreaker &&
                       lastMove == other.lastMove &&
                       currentTerrain == other.currentTerrain;
            }
        };
        vector<State> visitedStates;
        
        bool isInLoop();
        void south();
        void east();
        void north();
        void west();

        bool forcedMove(char c);
        bool newMove(bool changeDir = false);
        bool teleport();

        bool isAccessible(int xVar, int yVar);
        bool canMove(bool changeDir, string move, int xVar, int yVar);

    public :
        Robot(int xVar, int yVar, vector<string> &grid, vector<pair<int,int>>& tp);
        void move();

};

Robot::Robot(int xVar, int yVar, vector<string> &grid, vector<pair<int,int>>& tp)
    :   x(xVar), 
        y(yVar), 
        modeReverse(false), 
        grid(grid), 
        lastMove("SOUTH"),
        teleports(tp)
    {

    }
void Robot::south() 
{
  output.append("SOUTH\n");
  lastMove = "SOUTH";
  x++;
}

void Robot::east() 
{
  output.append("EAST\n");
  lastMove = "EAST";
  y++;
}

void Robot::north() 
{
  output.append("NORTH\n");
  lastMove = "NORTH";
  x--;
}

void Robot::west() 
{
  output.append("WEST\n");
  lastMove = "WEST";
  y--;
}

bool Robot::forcedMove(char c) 
{
    if(c == 'S')
    {
        south();
        return true;
    }
    else if(c == 'E')
    {
        east();
        return true;
    }   
    else if(c == 'N')
    {
        north();
        return true;
    }  
    else if (c == 'W')
    {
        west();
        return true;
    } 
    
    return false;
}

bool Robot::newMove(bool changeDir)
{
    if(modeReverse)
    {
        if(canMove(changeDir, "WEST", x, y-1)) 
        {
            west();
            return true;
        }
        else if(canMove(changeDir, "NORTH", x-1, y)) 
        {
            north();
            return true;
        }
        else if(canMove(changeDir, "EAST", x, y+1))
        {
            east();
            return true;
        }
        else if(canMove(changeDir, "SOUTH", x+1, y))
        {
            south();
            return true;
        }
    }
    else
    {
        if(canMove(changeDir, "SOUTH", x+1, y))
        {
            south();
            return true;
        }
        else if(canMove(changeDir, "EAST", x, y+1))
        {
            east();
            return true;
        }
        else if(canMove(changeDir, "NORTH", x-1, y))
        {
            north();
            return true;
        }
        else if(canMove(changeDir, "WEST", x, y-1))
        {
            west();
            return true;
        }

    }
    // si on n'a pas essayé de changer de direction
    // on rappelle la fonction pour une nouvelle tentative
    // si on a déjà essayé , on retrouve FALSE
    return (changeDir? false : newMove(true));
}

bool Robot::teleport()
{
    if(teleports.empty() || teleports.size()<2)
        return false;

    if(x == teleports[0].first && y == teleports[0].second)
    {
        x = teleports[1].first;
        y = teleports[1].second;
        return true;
    }
    else if(x == teleports[1].first && y == teleports[1].second)
    {
        x = teleports[0].first;
        y = teleports[0].second;
        return true;
    }

    return false;
}

bool Robot::isAccessible(int xVar, int yVar) 
{
    return ((modeBreaker || grid[xVar][yVar] != 'X') && grid[xVar][yVar] != '#');
}

bool Robot::canMove(bool changeDir, string move, int xVar, int yVar)
{
    return (changeDir || lastMove == move) && isAccessible(xVar, yVar);
}

bool Robot::isInLoop() 
{
    State currentState = {x, y, modeReverse, modeBreaker, lastMove, grid[x][y]};
    for (const auto& state : visitedStates) 
    {
        if (state == currentState) return true;
    }
    visitedStates.push_back(currentState);
    return false;
}

void Robot::move()
{
    bool end = false;
    while (!end) 
    {
        if (isInLoop()) {
            output= "LOOP\n";
            end = true;
            continue;
        }

        bool move = false;
        char currentPos = grid[x][y];  
    
        if(currentPos == 'B') modeBreaker = !modeBreaker;

        if(currentPos == 'I') modeReverse = !modeReverse;

        if(currentPos == 'X' && modeBreaker)
        {
            // obstacle détruit
            grid[x][y] = ' '; 
        }

        if(currentPos == 'T') move = teleport();

        // movement forcé   
        move = forcedMove(currentPos);

        if(!move) move = newMove();

        if(!end) end = grid[x][y] == '$';
    }

  cout << output;

}

int main() 
{
    int l;
    int c;
    cin >> l >> c;
    cin.ignore();
    vector<string> grid;
    vector<pair<int,int>> tp;
    pair<int, int> startPos;
    for (int i = 0; i < l; i++) 
    {
        string line;
        getline(cin, line);
        grid.push_back(line);

        for (int j = 0; j < c; j++)
        {
            char c = grid[i][j];
            if (c == '@') startPos = {i, j};
            if(c == 'T') tp.push_back({i,j});
        }
            
    }

    Robot blunder(startPos.first, startPos.second, grid, tp);

    blunder.move();  
}