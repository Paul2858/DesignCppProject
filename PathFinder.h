#ifndef PATHFINDER
#define PATHFINDER
#include "Graph.h"

// template<typename GraphNodeList>
// concept GraphLike = requires(GraphNodeList list) {
//   requires std::forward_iterator<typename GraphNodeList::iterator>;
//   requires std::forward_iterator<typename GraphNodeList::const_iterator>;
//   { list.begin() } -> std::same_as<typename GraphNodeList::iterator>;
//   { list.end() } -> std::same_as<typename GraphNodeList::iterator>;
//   { list.begin() } -> std::same_as<typename GraphNodeList::const_iterator>;
//   { list.end() } -> std::same_as<typename GraphNodeList::const_iterator>;
// };

class PathFinder {
public:
	// PathFinder(Graph g);
  // template<typename G, typename UID>
  //   requires GraphLike(G) && UniqueID(UID)
	// static std::vector<Edge> AStar(G &graph, UID start, UID end);
	static std::vector<int> AStar(Graph &graph, int start, int end);
// private:
// 	Graph &graph;
};
#endif