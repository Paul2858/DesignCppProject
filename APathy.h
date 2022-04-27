#ifndef APATHY
#define  APATHY
#include <concepts>
#include <iterator>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <typeinfo>

// #######
# define INF 0x3f3f3f3f
// ######

/************************ CONCEPTS ************************/
template<typename WVal>
concept Weight = requires () {
  requires std::totally_ordered<WVal>;
};

template<typename EStruct>
concept EdgeLike = requires(EStruct e) {
  requires std::same_as<decltype(e.src), decltype(e.dest)>;
  requires Weight<decltype(e.weight)>;
};
/**********************************************************/

template<typename E, typename ID, typename W>
  requires EdgeLike<E> && Weight<W>
class APathy {
public:
  std::unordered_map<ID, std::vector<std::pair<ID, W>>> adjList;
  APathy(std::vector<E> &edges) {
    for (auto &edge : edges) {
      if (adjList.find(edge.src) == adjList.end()) {
        std::vector<std::pair<ID, W>> newVector;
        adjList[edge.src] = newVector;
      }
      adjList[edge.src].push_back(std::make_pair(edge.dest, edge.weight));
    }
  };


  std::vector<ID> AStar(ID start, ID end) {
    std::vector<ID> reconstructedPath;
    std::set<ID> openSet {start};
    std::set<ID> closedSet;

    std::map<ID, W> g;
    std::map<ID, ID> parents;

    g[start] = 0;
    parents[start] = start;

    while (openSet.size() > 0) {
      ID blank;
      ID n;
      for (ID v : openSet) {
        // if (n == NULL || (g[v] + 1 /* heuristic [v] */ < g[n] + 1 /* heuristic [n] */ )) {
        if (n == blank || (g[v] + 1) < (g[n] + 1)) {
          n = v;
        }
      }

      if (n == blank) {
        return reconstructedPath;
      }
      if (n == end) {
        while (parents[n] != n) {
          reconstructedPath.push_back(n);
          n = parents[n];
        }
        reconstructedPath.push_back(start);
        std::reverse(reconstructedPath.begin(), reconstructedPath.end());
        return reconstructedPath;
      }
      for (auto pair : adjList[n]) {
        ID m = pair.first;
        W weight = pair.second;
        if (std::find(openSet.begin(), openSet.end(), m) == openSet.end() ||
            std::find(closedSet.begin(), openSet.end(), m) == closedSet.end()) {
          openSet.insert(m);
          parents[m] = n;
          g[m] = g[n] + weight;
        } else {
          if (g[m] > (g[n] + weight)) {
            g[m] = g[n] + weight;
            parents[m] = n;

            if (std::find(closedSet.begin(), closedSet.end(), m) != closedSet.end()) {
              closedSet.erase(m);
              openSet.insert(m);
            }
          }
        }
      }
      openSet.erase(n);
      closedSet.insert(n);
    }

    return reconstructedPath;
  };

  // ####################
  std::vector<ID> Dijkstra(ID src, ID dest) {
    // Create a set to store vertices that are being
    // processed
    std::set<std::pair<W, ID>> setds;
    int V = adjList.size();

    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    std::map<ID, W> dist; // (V, INF);
    std::map<ID, ID> prev_nodes;

    setds.insert(make_pair(0, src));
    dist[src] = 0;
    prev_nodes[src] = src;

    while (!setds.empty())
    {
        // The first vertex in Set is the minimum distance
        // vertex, extract it from set.
        // --- Pair tmp = *(setds.begin());
        std::pair<W, ID> tmp =  *(setds.begin());
        setds.erase(setds.begin());
 
        // vertex label is stored in second of pair
        ID u = tmp.second;
 
        typename std::vector<std::pair<ID, W>>::iterator i;
        // --- for (i = adjList[u].begin(); i != adjList[u].end(); ++i)
        for (i = adjList[u].begin(); i != adjList[u].end(); ++i)
        {   
            // Get vertex label and weight of current adjacent of u.
            ID v = (*i).first;
            W weight = (*i).second;
            
            // ########
            if (dist.find(v) == dist.end()) {
              dist[v] = INF;
            }
            // #######

            //    If there is shorter path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                /*  If distance of v is not INF then it must be in
                    our set, so removing it and inserting again
                    with updated less distance. */
                // --- if (dist[v] != INF) {
                // if (dist.find(v) != dist.end()) {
                //     setds.erase(setds.find(make_pair(dist[v], v)));
                // }
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

    std::vector<ID> path;
    while (prev_nodes[dest] != dest) {
        path.push_back(dest);
        dest = prev_nodes[dest];
    }
    path.push_back(src);

    std::reverse(path.begin(), path.end());
    return path;
  };

};
#endif