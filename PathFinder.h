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
template<typename E, typename ID, typename W>
class PathFinder {
public:
	static std::vector<ID> AStar(Graph<E, ID, W> &graph, ID start, ID end);
};
#endif