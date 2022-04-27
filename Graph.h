#ifndef GRAPH
#define  GRAPH
#include <concepts>
#include <iterator>
#include <vector>
#include <unordered_map>

template<typename WVal>
concept Weight = requires () {
  requires std::totally_ordered<WVal>;
};

template<typename E>
concept EdgeLike = requires(E e) {
  requires std::same_as<decltype(e.src), decltype(e.dest)>;
  requires Weight<decltype(e.weight)>;
};

template<typename E, typename ID, typename W>
class Graph {
public:
  std::unordered_map<ID, std::vector<std::pair<ID, W>>> adjList;
  Graph(std::vector<E> &edges) {
    for (auto &edge : edges) {
      if (adjList.find(edge.src) == adjList.end()) {
        std::vector<std::pair<ID, W>> newVector;
        adjList[edge.src] = newVector;
      }
      adjList[edge.src].push_back(std::make_pair(edge.dest, edge.weight));
    }
  }
};
#endif