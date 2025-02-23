#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <math.h>

using namespace std;

class Ship
{

    const int MAX_VX = 20;
    const int MAX_VY = 40;
    const int MARGIN = 5;
    const int MARGIN_LAND = 400;
    const double GRAVITY = 3.711;

public:
    Ship() {}
    void initialise(int x, int y, int hs, int vs, int f, int r, int p)
    {
        mX = x;
        mY = y,
        mVx = hs;
        mVy = vs;
        mFuel = f;
        mAngle = r;
        mPower = p;
    }

    void setLandTarget(int landX1, int landX2, int landY0)
    {
        mLandStart = landX1;
        mLandEnd = landX2;
        mLandY = landY0;
    }

    bool isOnTarget()
    {
        return (mLandStart <= mX && mX <= mLandEnd);
    }
    bool isCloseToLand()
    {
        return abs(mLandY - mY) < 100;
    }

    bool isTooFastHorizontally()
    {
        return abs(mVx) > 4 * MAX_VX;
    }

    bool isTooFastVertically()
    {
        return abs(mVy) > MAX_VY - MARGIN;
    }

    bool isTooSlowHorizontally()
    {
        return abs(mVx) < MAX_VX * 2;
    }

    bool isNotGoingToTarget()
    {
        return mX < mLandStart && mVx < 0 || mX > mLandEnd && mVx > 0;
    }

    int angleToCompensateHS()
    {
        int res;
        double hypotenuse = sqrt(mVx * mVx + mVy * mVy);
        double angle = asin(mVx / hypotenuse) * 180 / M_PI; // in degrees
        return int(angle);
    }

    int angleToTarget()
    {
        int angle = 0;
        if (mLandStart > mX)
        {
            angle = -33;
        }
        else if (mLandEnd < mX)
            angle = 33;

        return angle;
    }

    pair<int, int> landing()
    {

        pair<int, int> sortie({0, 0});
        sortie.first = 0;
        if (isCloseToLand())
        {
            sortie.first = 0;
            sortie.second = 2;
        }
        else if (abs(mVx) > 1)
        {
            sortie.first = this->angleToCompensateHS();

            sortie.second = min(mPower + 1, 4);
        }
        else
        {
            if (abs(mVy) >= MAX_VY - MARGIN && mPower < 4)
                sortie.second = mPower + 1;
            else if (abs(mVy) < MAX_VY - MARGIN && mPower != 0)
                sortie.second = mPower - 1;
            else
                sortie.second = mPower;
        }
        return sortie;
    }

private:
    int mX, mY, mVx, mVy, mFuel, mAngle, mPower, mLandStart, mLandEnd, mLandY;
};

int main()
{
    int n; // the number of points used to draw the surface of Mars.
    cin >> n;
    cin.ignore();
    vector<pair<int, int>> points;
    for (int i = 0; i < n; i++)
    {
        int land_x; // X coordinate of a surface point. (0 to 6999)
        int land_y; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> land_x >> land_y;
        cin.ignore();

        points.push_back({land_x, land_y});
    }

    Ship marsLander = Ship();
    pair<int, int> land_start({0, 0}), land_end({0, 0});
    for (auto p : points)
    {
        if (land_start.first == 0 && land_start.second == 0)
            land_start = p;
        else
        {
            if (land_start.second == p.second)
            {
                land_end = p;
                marsLander.setLandTarget(land_start.first, land_end.first, land_end.second);
                cerr << land_start.first << " " << land_end.first << endl;
                break;
            }
            else
            {
                land_start = p;
            }
        }
    }

    // game loop
    while (1)
    {
        int x;
        int y;
        int hs; // the horizontal speed (in m/s), can be negative.
        int vs; // the vertical speed (in m/s), can be negative.
        int f;  // the quantity of remaining fuel in liters.
        int r;  // the rotation angle in degrees (-90 to 90).
        int p;  // the thrust power (0 to 4).
        cin >> x >> y >> hs >> vs >> f >> r >> p;
        cin.ignore();
        marsLander.initialise(x, y, hs, vs, f, r, p);

        if (marsLander.isOnTarget())
        {
            pair<int, int> s = marsLander.landing();
            cout << s.first << " " << s.second << endl;
        }
        else
        {
            if (marsLander.isTooFastHorizontally() || marsLander.isNotGoingToTarget())
                cout << marsLander.angleToCompensateHS() << " 4" << endl;
            else if (marsLander.isTooSlowHorizontally())
                cout << marsLander.angleToTarget() << " 4" << endl;
            else
            {
                if (abs(vs) > 0)
                    cout << "0 4" << endl;
                else
                    cout << "0 3" << endl;
            }
        }
    }
}