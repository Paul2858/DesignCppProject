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
};
#endif