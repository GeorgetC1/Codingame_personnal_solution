#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Node 
{
    unordered_map<int, Node*> children;
};

// function to search a key in a BST
Node* search(Node* root, int key) {
  
    if (root == NULL)
        return root;

    // Cherche dans les enfants directs
    auto it = root->children.find(key);
    if (it != root->children.end())
        return it->second;

    // Cherche récursivement dans les sous-arbres
    for(const auto& [nodeKey, childNode] : root->children)
    {
        Node* res = search(childNode, key);
        if(res != NULL)
            return res;
    }

    return NULL; // not found
}

int browseTree(Node* root) 
{
    if (root == nullptr || root->children.empty())
        return 0;

    int maxDepth = 0;  // Pour la racine, on commence à 0
    for(const auto& [key, child] : root->children)
    {
        maxDepth = max(maxDepth, browseTree(child));
    }

    return maxDepth + 1;
}

int main()
{
    int n; // the number of relationships of influence
    cin >> n; cin.ignore();
    Node* root = new Node;
    for (int i = 0; i < n; i++) {
        int x; // a relationship of influence between two people (x influences y)
        int y;
        cin >> x >> y; cin.ignore();

        Node* nodeX = search(root, x);
        if(nodeX == NULL)
        {
            root->children[x] = new Node;
            nodeX = root->children[x];
        }

        Node* nodeY = search(root, y);
        if(nodeY == NULL)
        {
            nodeY = new Node;
        }

        nodeX->children[y] = nodeY;
        
    }


    // The number of people involved in the longest succession of influences
    cout << browseTree(root) << endl;
}