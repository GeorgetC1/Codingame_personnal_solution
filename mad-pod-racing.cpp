#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

 bool shouldUseBoost(int dist, int angle)
 {

    if( dist > 6500 && abs(angle) < 20)
        return true;

    return false;
 }

int main()
{

    int boostReserve = 1;
    // game loop
    while (1) {
        int x;
        int y;
        int next_checkpoint_x; // x position of the next check point
        int next_checkpoint_y; // y position of the next check point
        int next_checkpoint_dist; // distance to the next checkpoint
        int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> next_checkpoint_x >> next_checkpoint_y >> next_checkpoint_dist >> next_checkpoint_angle; cin.ignore();
        int opponent_x;
        int opponent_y;
        cin >> opponent_x >> opponent_y; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        int thrust = 0;
        if(next_checkpoint_angle > 90 || next_checkpoint_angle < -90)
            thrust = 0;
        else 
        {
                thrust = 100;
        }
            

        bool useBoost = (boostReserve>0);

        if(boostReserve >0 && useBoost)
            boostReserve --;
        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"

        cerr << next_checkpoint_x - x << " " << next_checkpoint_y - y << " " << next_checkpoint_angle << " " << next_checkpoint_dist << endl;

        if(useBoost)
        {
            cout << next_checkpoint_x << " " << next_checkpoint_y << " " << "BOOST" << endl;
        }
        else
            cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust<< endl;
        
    }
}