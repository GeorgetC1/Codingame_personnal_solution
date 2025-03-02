#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node
{
    // unordered_map au lieu de map pour aller plus vite 
    // on a pas besoin de données triées
    unordered_map<char, Node*> children; 
};

int main()
{
    int n;
    cin >> n; cin.ignore();

    Node* tree= new Node;
    int size = 0;
    for (int i = 0; i < n; i++) {
        string telephone;
        cin >> telephone; cin.ignore();

        Node* current = tree; // initialisation à la racine de l'arbre
        for(auto num : telephone)
        {
            // on trouve pas le numéro , on l'ajoute
            if(current->children.find(num) == current->children.end())
            {
                current->children[num] = new Node;
                size++;
            }

            current = current->children[num];
        }
    }
    
    cout << size << endl;
}