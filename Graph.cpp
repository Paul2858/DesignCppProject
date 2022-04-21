// https://www.techiedelight.com/graph-implementation-using-stl/

#include <iostream>
#include <vector>

struct Edge
{
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph
{
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges, int n)
    {
        adjList.resize(n);

        for (auto &edge : edges)
        {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
        }
    }
};

void printGraph(Graph const &graph, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (Pair v : graph.adjList[i])
        {
            std::cout << "(" << i << ", " << v.first << ", " << v.second << ") ";
        }
        std::cout << std::endl;
    }
}
