#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

struct Node
{
    Node() : isGateway(false) {}
    set<int> listNode;
    bool isGateway;
    set<int> listGateway;
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
pair<int, int> breadth_first_search(const vector<Node> &graph,
                                    int start)
{
    queue<int> frontier;
    frontier.push(start);

    vector<bool> reached(graph.size(), false);
    reached[start] = true;

    int resId = -1;
    while (!frontier.empty())
    {
        int current = frontier.front();
        frontier.pop();

        reached[current] = true;
        Node nCurrent = graph[current];

        if (nCurrent.listGateway.size() > 1)
        {
            resId = current;
            break;
        }
        else if (nCurrent.listGateway.size() == 1)
        {
            if (resId == -1)
            {
                resId = current;
                if (resId == start)
                    break;
            }
            for (int next : nCurrent.listNode)
            {
                if (reached[next] == false)
                {
                    frontier.push(next);
                }
            }
        }
        else if (resId == -1)
        {
            for (int next : nCurrent.listNode)
            {
                if (reached[next] == false)
                {
                    frontier.push(next);
                }
            }
        }
    }
    return make_pair(resId, *(graph[resId].listGateway.begin()));
}

int main()
{
    int n; // the total number of nodes in the level, including the gateways
    int l; // the number of links
    int e; // the number of exit gateways
    cin >> n >> l >> e;
    cin.ignore();

    vector<Node> graph(n, Node());
    for (int i = 0; i < l; i++)
    {
        int n1; // N1 and N2 defines a link between these nodes
        int n2;
        cin >> n1 >> n2;
        cin.ignore();

        graph[n1].listNode.insert(n2);
        graph[n2].listNode.insert(n1);
    }

    for (int i = 0; i < e; i++)
    {
        int ei; // the index of a gateway node
        cin >> ei;
        cin.ignore();

        graph[ei].isGateway = true;

        for (const auto &p : graph[ei].listNode)
            graph[p].listGateway.insert(ei);
    }

    // game loop
    while (1)
    {
        int si; // The index of the node on which the Bobnet agent is positioned this turn
        cin >> si;
        cin.ignore();

        pair<int, int> res = breadth_first_search(graph, si);

        cout << res.first << " " << res.second << endl;

        graph[res.first].listGateway.erase(res.second);
        graph[res.first].listNode.erase(res.second);
        graph[res.second].listNode.erase(res.first);
    }
}