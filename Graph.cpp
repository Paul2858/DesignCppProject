// #include "Graph.h"

// Graph::Graph(std::vector<E> &edges) {
//     for (auto &edge : edges)
//     {
//         if (adjList.find(edge.src) == adjList.end()) {
//             // adjList[edge.src].insert(
//             //     std::vector<std::pair<ID, W>>
//             // );
//             adjList[edge.src].insert({std::make_pair(edge.dest, edge.weight)})
//         } else {
//             adjList[edge.src].push_back(std::make_pair(edge.dest, edge.weight));
//         }
//     }
// }