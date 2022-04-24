#include "Graph.h"

Graph::Graph(std::vector<Edge> &edges, int n) {
    adjList.resize(n);

    for (auto &edge : edges)
    {
        int src = edge.src;
        int dest = edge.dest;
        int weight = edge.weight;

        adjList[src].push_back(std::make_pair(dest, weight));
    }
}

void printGraph(Graph const &graph, int n) {
    for (int i = 0; i < n; i++)
    {
        for (Pair v : graph.adjList[i])
        {
            std::cout << "(" << i << ", " << v.first << ", " << v.second << ") ";
        }
        std::cout << std::endl;
    }
}
