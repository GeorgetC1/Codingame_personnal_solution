#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
set<string> getCards(string exp)
{
    vector<char> ranks, suits;
    for (auto &c : exp)
    {
        switch(c)
        {
            case '2':  
            case '3':
            case '4':  
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'T':
            case 'J':
            case 'Q':
            case 'K':
            case 'A':
                ranks.push_back(c);
                break;
            case 'C':
            case 'D':
            case 'H':
            case 'S':
                suits.push_back(c);
                break;

        }
    }

    if(ranks.empty()) ranks = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
    if(suits.empty()) suits = {'C','D','H','S'};

    set<string> cards;
    for(auto &rank : ranks)
    {
        for(auto &suit : suits)
        {
            string card;
            card.push_back(rank);
            card.push_back(suit);
            cards.insert(card);
        }
    }
    return cards;
}

int main()
{
    int r;
    int s;
    cin >> r >> s; cin.ignore();
    
    set<string> removedCards;
    for (int i = 0; i < r; i++) {
        string removed;
        getline(cin, removed);
        
        set<string> tmp = getCards(removed);
        removedCards.insert(tmp.begin(), tmp.end());
    }

    set<string> soughtCards;
    for (int i = 0; i < s; i++) {
        string sought;
        getline(cin, sought);
        set<string> tmp = getCards(sought);
        
        for(auto& tmpString : tmp)
        {
            if(!(removedCards.contains(tmpString)))
            {
                soughtCards.insert(tmpString);
            }
        }
    }


    double nbCards = soughtCards.size();
    int pack = 52 - removedCards.size();;
    int pourcentage = nbCards/pack*100;
    cout <<  pourcentage <<'%' << endl;
}