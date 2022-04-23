#include<iostream>
#include<climits>
#include <vector>
#include <set>
#include <list>
#include "Graph.h"

# define INF 0x3f3f3f3f
using namespace std;


void dijkstra_algo(Graph graph, int src)
{
    // https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-set-in-stl/
    vector<vector<Pair> > adj = graph.adjList;
    int V = adj.size();

    // Create a set to store vertices that are being
    // processed
    set< Pair > setds;
 
    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    vector<int> dist(V, INF);
    vector<int> prev_nodes(V, -1);
 
    // Insert source itself in Set and initialize its
    // distance as 0.
    setds.insert(make_pair(0, src));
    dist[src] = 0;
 
    /* Looping till all shortest distance are finalized
       then setds will become empty    */
    while (!setds.empty())
    {
        // The first vertex in Set is the minimum distance
        // vertex, extract it from set.
        Pair tmp = *(setds.begin());
        setds.erase(setds.begin());
 
        // vertex label is stored in second of pair
        int u = tmp.second;
 
        vector<Pair>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent of u.
            int v = (*i).first;
            int weight = (*i).second;
            printf("u, v, weight: %d %d %d\n", u, v, weight);
 
            //    If there is shorter path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                /*  If distance of v is not INF then it must be in
                    our set, so removing it and inserting again
                    with updated less distance. */
                if (dist[v] != INF) {
                    setds.erase(setds.find(make_pair(dist[v], v)));
                }
 
                // Updating distance of v
                dist[v] = dist[u] + weight;
                // Updating the list of previous nodes
                prev_nodes[v] = u;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }

    // the value target=4 below is just a placeholder to demo that 
    // we can get a path from source to target. we could later add
    // a functionality where a use puts a target and we return 
    // the shortest path.
    int target = 4;
    vector<int> path;
    while (prev_nodes[target] != -1) {
        path.push_back(target);
        target = prev_nodes[target];
    }
    path.push_back(target);

    printf("below is the path\n");
    for (int i = 0; i < path.size(); i++) {
        printf("path node: %d\n", path[i]);
    }

 
    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}