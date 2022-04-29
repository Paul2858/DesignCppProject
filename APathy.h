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
#include <deque>
#include <stack>

# define INF 0x3f3f3f3f

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
  std::vector<ID> AStar(ID start, ID end, W (*h)(ID)) {
    std::vector<ID> reconstructedPath;

    int startIdx = getIdx(start);
    int endIdx   = getIdx(end);
    std::set<int> openSet {startIdx};
    std::set<int> closedSet;

    std::map<int, W> g;
    std::map<int, int> parents;

    g[startIdx] = 0;
    parents[startIdx] = startIdx;

    while (openSet.size() > 0) {
      int n = -1;
      for (int v : openSet) {
        if (n == -1 || (g[v] + h(vals[v]) < g[n] + h(vals[n]) )) {
          n = v;
        }
      }

      if (n == -1) {
        return reconstructedPath;
      }
      if (n == endIdx) {
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
        if (std::find(openSet.begin(), openSet.end(), m) == openSet.end() &&
            std::find(closedSet.begin(), closedSet.end(), m) == closedSet.end()) {
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
  std::vector<ID> BreadthFirstSearch(ID start, ID target) {
    std::vector<bool> visited(adjList.size(), false);
    std::deque<ID> stack;
    std::vector<ID> path;

    stack.push_back(start);

    while (!stack.empty())
    {
      ID s = stack.front();
      int sIdx = getIdx(s);
      if (s == target) {
        path.push_back(s);
        return path;
      }

      stack.pop_front();

      if (!visited[sIdx])
      {
        path.push_back(s);
        //std::cout << s << " ";
        visited[sIdx] = true;
      }

      for (auto i = adjList[sIdx].begin(); i != adjList[sIdx].end(); ++i)
      {
        if (!visited[(*i).first])
          stack.push_back(vals[(*i).first]);
      }
    }
    return {};
  };
  std::vector<ID> DepthFirstSearch(ID start, ID target) {
      std::vector<bool> visited(adjList.size(), false);
      std::stack<ID> stack;
      std::vector<ID> path;

      stack.push(start);

      while (!stack.empty())
      {
        ID s = stack.top();
        int sIdx = getIdx(s);
        if (s == target) {
          path.push_back(s);
          return path;
        }

        stack.pop();

        if (!visited[sIdx])
        {
          path.push_back(s);
          //std::cout << s << " ";
          visited[sIdx] = true;
        }

        for (auto i = adjList[sIdx].begin(); i != adjList[sIdx].end(); ++i)
        {
          if (!visited[(*i).first])
            stack.push(vals[(*i).first]);
        }
      }
      return {};
  };
  std::vector<ID> Dijkstra(ID start, ID end) {
    using namespace std;
    typedef std::pair<int, W> Pair;
    int src = getIdx(start);

    int V = adjList.size();

    // Create a set to store vertices that are being
    // processed
    std::set< Pair > setds;
 
    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    std::vector<int> dist(V, INF);
    std::vector<int> prev_nodes(V, -1);
 
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
 
        typename vector<Pair>::iterator i;
        for (i = adjList[u].begin(); i != adjList[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent of u.
            int v = (*i).first;
            int weight = (*i).second;
 
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
    int target = getIdx(end);
    std::vector<ID> path;
    while (prev_nodes[target] != -1) {
        path.push_back(vals[target]);
        target = prev_nodes[target];
    }
    path.push_back(vals[target]);

    std::reverse(path.begin(), path.end());
    return path;
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