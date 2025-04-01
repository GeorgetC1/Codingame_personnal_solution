#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    unordered_map<char, int> letterScores = {
        {'e', 1}, {'a', 1}, {'i', 1}, {'o', 1}, {'n', 1}, 
        {'r', 1}, {'t', 1}, {'l', 1}, {'s', 1}, {'u', 1},
        {'d', 2}, {'g', 2},
        {'b', 3}, {'c', 3}, {'m', 3}, {'p', 3},
        {'f', 4}, {'h', 4}, {'v', 4}, {'w', 4}, {'y', 4},
        {'k', 5},
        {'j', 8}, {'x', 8},
        {'q', 10}, {'z', 10}
    };

    int n;
    cin >> n; cin.ignore();
    vector<string> dict(n);
    for (int i = 0; i < n; i++) {
        getline(cin, dict[i]);
    }
    string letters;
    getline(cin, letters);

    // Utilisation d'un array de comptage pour les lettres qu'on a en entrée
    array<int, 26> letterCount = {0};
    for (char l : letters) {
        letterCount[l - 'a']++;
    }

    string bestWord;
    int maxScore = 0;

    for (const string& word : dict) {
        array<int, 26> wordCount = {0};
        int score = 0;
        bool isValid = true;

        for (char c : word) {
            wordCount[c - 'a']++;
            if (wordCount[c - 'a'] > letterCount[c - 'a']) {
                isValid = false;
                break;
            }
            score += letterScores[c];
        }

        if (isValid && score > maxScore) {
            maxScore = score;
            bestWord = word;
        }
    }

    cout << bestWord << endl;
}