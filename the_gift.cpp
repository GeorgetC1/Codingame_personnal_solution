#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Pilipius
{
    private :
    int m_budget;
    int m_expenses;

    public :
    Pilipius(int budget) : m_budget(budget), m_expenses(0) {}

    bool canGive() { return (m_budget-m_expenses) > 0; }
    bool hasGiven() { return m_expenses > 0; }
    int getExpenses() const { return m_expenses; }
    void give() { m_expenses ++; }

    bool operator<(const Pilipius& other)
    {
        return this->getExpenses() < other.getExpenses();
    }
};



int main()
{
    int n;
    cin >> n; cin.ignore();
    int c;
    cin >> c; cin.ignore();

    vector<Pilipius> list;
    int total = 0;
    for (int i = 0; i < n; i++) {
        int b;
        cin >> b; cin.ignore();
        total += b;

        list.push_back(Pilipius(b));
    }

    if(total < c)
        cout << "IMPOSSIBLE" << endl;
    else
    {
        int budget = 0;
        while (budget != c)
        {
            for(int i = list.size() - 1 ; i >= 0 && budget != c; i--)
            {
                if(list[i].canGive())
                {
                    list[i].give();
                    budget++;
                }                
            }
        }
        
        std::sort(list.begin(),list.end());
        for(auto pili : list)
        {
            cout << pili.getExpenses() << endl;
        }
    }


}