#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Player
{
    private :
        pair<int,int> mCurrPos;
        string mLastPos;
        vector<vector<int>> mGrid;

    public:
        // constructor
        Player();
        Player(pair<int,int> currPos,vector<vector<int>> grid);

        // moves
        void down();
        void left();
        void right();

        // gameplay
        void play();
        void nextMove();


};
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 Player::Player(pair<int,int> currPos,vector<vector<int>> grid)
    :mCurrPos(currPos), mLastPos({0,0}), mGrid(grid)
 {
 }

void Player::down() { mCurrPos.second++; }
void Player::left() { mCurrPos.first--; }
void Player::right() { mCurrPos.first++; }

void Player::play()
 {
    // game loop
    while (1) {
        int xi;
        int yi;
        string pos;
        cin >> xi >> yi >> pos; cin.ignore();

        mCurrPos.first = xi;
        mCurrPos.second = yi;
        mLastPos = pos;

        nextMove();
    }
 }
 
void Player::nextMove()
 {
    int type = mGrid[mCurrPos.first][mCurrPos.second];
    switch(type)
    {
        case 1:
        case 3:
        case 7:
        case 8:
        case 9:
        case 12:
        case 13:
            down();
            break;
        case 2:
            if(mLastPos == "RIGHT")
                left();
            else
                right();

            break;
        case 4:
            if(mLastPos == "RIGHT")
                down();
            else
                left();

            break;
        case 5:
            if(mLastPos == "LEFT")
                down();
            else
                right();

            break;
        case 6: 
            if(mLastPos == "RIGHT")
                left();
            else if(mLastPos == "LEFT")
                right(); 
            break;
        case 10:
            left();
            break;
        case 11:
            right();
            break;

        default:
            right();
            break;
    }

    // One line containing the X Y coordinates of the room in which you believe Player will be on the next turn.
    cout << mCurrPos.first << " " << mCurrPos.second << endl;
 }

int main()
{
    int w; // number of columns.
    int h; // number of rows.
    cin >> w >> h; cin.ignore();
    vector<vector<int>> grid(w, vector<int>(h,0));
    int type {0};
    for (int i = 0; i < h; i++) 
    {
        for (int j=0; j < w; j++)
        {
            cin >> type;
            grid[j][i]=type;
        }
    }
    int ex; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    cin >> ex; cin.ignore();

    // init the player
    Player indy({0,0}, grid);
    // play the loop
    indy.play();

}