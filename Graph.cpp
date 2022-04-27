// #include "Graph.h"

// template<typename E, typename ID, typename W>
//   requires EdgeLike<E> && Weight<W>
// Graph<E, ID, W>::Graph(std::vector<E> &edges) {
//   for (auto &edge : edges) {
//     if (adjList.find(edge.src) == adjList.end()) {
//       std::vector<std::pair<ID, W>> newVector;
//       adjList[edge.src] = newVector;
//     }
//     adjList[edge.src].push_back(std::make_pair(edge.dest, edge.weight));
//   }
// }