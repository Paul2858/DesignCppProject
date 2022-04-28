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
  APathy(std::vector<E> &edges, int n) {
    adjList.resize(n);
    int i = 0;
    for (auto &edge : edges) {
      int foundSrc  = -1;
      int foundDest = -1;
      for ( const auto &[key, value]: vals ) {
        if (value == edge.src) {
          foundSrc = key;
        }
        if (value == edge.dest) {
          foundDest = key;
        }
      }
      if (foundSrc == -1) {
        foundSrc = i;
        vals[foundSrc] = edge.src;
        i++;
      }
      if (foundDest == -1) {
        foundDest = i;
        vals[foundDest] = edge.dest;
        i++;
      }
      adjList[foundSrc].push_back(std::make_pair(foundDest, edge.weight));
    }
  };
  std::vector<ID> AStar(ID start, ID end) {
    std::vector<ID> reconstructedPath;

    int startIdx = getIdx(start);
    std::set<int> openSet {startIdx};
    std::set<int> closedSet;

    std::map<int, W> g;
    std::map<int, int> parents;

    g[startIdx] = 0;
    parents[startIdx] = startIdx;

    while (openSet.size() > 0) {
      int n = -1;
      for (int v : openSet) {
        if (n == -1 || (g[v] + 1 /* heuristic [v] */ < g[n] + 1 /* heuristic [n] */ )) {
          n = v;
        }
      }

      if (n == -1) {
        return reconstructedPath;
      }
      if (vals[n] == end) {
        while (parents[n] != n) {
          reconstructedPath.push_back(vals[n]);
          n = parents[n];
        }
        reconstructedPath.push_back(start);
        std::reverse(reconstructedPath.begin(), reconstructedPath.end());
        return reconstructedPath;
      }
      for (auto &pair : adjList[n]) {
        int m = pair.first;
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
  void printAdjList() {
    std::cout << "{\n";
    for (int i = 0; i < (int) adjList.size(); i++) {
      std::cout << '\t' << vals[i] << ": [ ";
      for (int j = 0; j < (int) adjList[i].size(); j++)
        std::cout << "(" << vals[adjList[i][j].first] << "," << adjList[i][j].second << ") ";
      std::cout << "]\n";
    }
    std::cout << "}\n";
  };
  void printVals() {
    std::cout << "{\n";
    for ( const auto &[key, value]: vals ) {
      std::cout << '\t' << key << ": " << value << '\n';
    }
    std::cout << "}\n";
  };
private:
  std::vector<std::vector<std::pair<int, W>>> adjList;
  std::unordered_map<int, ID> vals;
  int getIdx(ID &id) {
    for ( const auto &[key, value]: vals ) {
      if (value == id) {
        return key;
      }
    }
    return -1;
  };
};
#endif