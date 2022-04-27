// #include "APathy.h"

// template<typename E, typename ID, typename W>
//   requires EdgeLike<E> && Weight<W>
// APathy<E, ID, W>::APathy(std::vector<E> &edges) {
//   for (auto &edge : edges) {
//     if (adjList.find(edge.src) == adjList.end()) {
//       std::vector<std::pair<ID, W>> newVector;
//       adjList[edge.src] = newVector;
//     }
//     adjList[edge.src].push_back(std::make_pair(edge.dest, edge.weight));
//   }
// };
// template<typename E, typename ID, typename W>
//   requires EdgeLike<E> && Weight<W>
// std::vector<ID> APathy<E, ID, W>::AStar(ID start, ID end) {
//   std::vector<ID> reconstructedPath;
//   std::set<ID> openSet {start};
//   std::set<ID> closedSet;

//   std::map<ID, W> g;
//   std::map<ID, ID> parents;

//   g[start] = 0;
//   parents[start] = start;

//   while (openSet.size() > 0) {
//     ID blank;
//     ID n;
//     for (ID v : openSet) {
//       // if (n == NULL || (g[v] + 1 /* heuristic [v] */ < g[n] + 1 /* heuristic [n] */ )) {
//       if (n == blank || (g[v] + 1) < (g[n] + 1)) {
//         n = v;
//       }
//     }

//     if (n == blank) {
//       return reconstructedPath;
//     }
//     if (n == end) {
//       while (parents[n] != n) {
//         reconstructedPath.push_back(n);
//         n = parents[n];
//       }
//       reconstructedPath.push_back(start);
//       std::reverse(reconstructedPath.begin(), reconstructedPath.end());
//       return reconstructedPath;
//     }
//     for (auto pair : adjList[n]) {
//       ID m = pair.first;
//       W weight = pair.second;
//       if (std::find(openSet.begin(), openSet.end(), m) == openSet.end() ||
//           std::find(closedSet.begin(), openSet.end(), m) == closedSet.end()) {
//         openSet.insert(m);
//         parents[m] = n;
//         g[m] = g[n] + weight;
//       } else {
//         if (g[m] > (g[n] + weight)) {
//           g[m] = g[n] + weight;
//           parents[m] = n;

//           if (std::find(closedSet.begin(), closedSet.end(), m) != closedSet.end()) {
//             closedSet.erase(m);
//             openSet.insert(m);
//           }
//         }
//       }
//     }
//     openSet.erase(n);
//     closedSet.insert(n);
//   }

//   return reconstructedPath;
// };