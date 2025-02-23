#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string magic_phrase;
    getline(cin, magic_phrase);

    string res;
    int index = 0;
    for (auto c : magic_phrase)
    {
        if (c == ' ')
            c = '[';

        int value = c - 'A' + 1 - index;
        index += value;

        cerr << value << endl;

        for (int i = 0; i < value; i++)
        {
            res += '+';
        }

        for (int i = value; i < 0; i++)
        {
            res += '-';
        }

        res += '.';
    }

    cout << res << endl;
}