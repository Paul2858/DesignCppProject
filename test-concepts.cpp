#include <concepts>
#include <iterator>
/*
Concept for graph input: {adjacency matrix of: node type, node type, weight type} (weight type comparable)
Concept for matrix input: {something indexable[][], free type}
*/
/*
  GRAPH INPUT (list):

  {0, 1, 6}, {1, 2, 7}, {2, 0, 5}, {2, 1, 4}, {3, 2, 10}, {5, 4, 1}, {4, 5, 3}
  {0, 1},    {1, 2},    {2, 0}

  {Tile1.ID, Tile2.ID, Score}, {}{}
  map of node-type / id (or address) to int index
  +
  adjacency list
  [
    0: [(1, 2), (2, 10)],
    1: [(0, 4)],
    2: [(1, 3), (0, 5)],
    ...
  ]
*/

template<typename Val>
concept Weight = requires () {
  requires std::totally_ordered<Val>;
};

template<typename Val>
concept UniqueID = requires(Val a, Val b) {
  // can be used as a hash == unique id
  requires !std::is_default_constructible<Val>();
  requires !std::is_copy_constructible<Val>();
  requires !std::is_move_constructible<Val>();
  requires !std::is_copy_assignable<Val>();
  requires !std::is_move_assignable<Val>();
};

template<typename S, typename D, typename W>
struct Edge {
  auto UniqueID(S);
  auto UniqueID(D);
  auto Weight(W);
};

template<typename GraphNodeList>
concept GraphLike = requires(GraphNodeList list) {
  requires std::forward_iterator<typename GraphNodeList::iterator>;
  requires std::forward_iterator<typename GraphNodeList::const_iterator>;
  { list.begin() } -> std::same_as<typename GraphNodeList::iterator>;
  { list.end() } -> std::same_as<typename GraphNodeList::iterator>;
  { list.begin() } -> std::same_as<typename GraphNodeList::const_iterator>;
  { list.end() } -> std::same_as<typename GraphNodeList::const_iterator>;
};

// PathFinder(GraphLike<Edge> adjacencyList) {}

/*
template<typename CT>
concept ContainerType = requires(CT a, const CT b) {
  requires forward_iterator<typename CT::iterator>;
  requires forward_iterator<typename CT::const_iterator>;
  { a.begin() } -> same_as<typename CT::iterator>;
  { a.end() } -> same_as<typename CT::iterator>;
  { b.begin() } -> same_as<typename CT::const_iterator>;
  { b.end() } -> same_as<typename CT::const_iterator>;
};

template<typename OP, typename Acc>
concept AccumulatedOperation = requires(OP op, Acc acc) {
  requires invocable<OP, Acc, Acc>;
  requires same_as<result_of_t<OP(Acc, Acc)>, Acc>;
};

template<typename Container, typename Operation, typename Accumulator>
Accumulator sum(Container c, Operation op, Accumulator acc) {
  for (auto ci = c.begin(); ci != c.end(); ci++) {
    auto element = *ci;
    acc = op(acc, element);
  }
  return acc;
}

template<typename Container, typename Operation, typename Accumulator>
  requires ContainerType<Container> && AccumulatedOperation<Operation, Accumulator>
Accumulator sumWithConcepts(Container c, Operation op, Accumulator acc) {
  for (auto ci = c.begin(); ci != c.end(); ci++) {
    auto element = *ci;
    acc = op(acc, element);
  }
  return acc;
}

int sum(vector<int> v, int acc) {
  for (auto vi = v.begin(); vi != v.end(); vi++) {
    int element = *vi;
    acc += element;
  }
  return acc;
}
*/

/*
  GRAPH INPUT (adjacency matrix)
  {
    NodeID: {NodeID NodeID NodeID},
    NodeID: {NodeID NodeID NodeID},
    NodeID: {NodeID NodeID NodeID}
  }
*/

/*
  MATRIX INPUT:
  {
    {0, 0, 0, 0, 1, 1, 0}
    {0, 0, 0, 0, 1, 1, 0}
    {0, 1, 0, 0, 1, 1, 0}
    {0, 1, 1, 0, 1, 1, 0}
    {0, 0, 1, 0, 0, 0, 0}
  }
  {
    0: {NodeId, NodeId, ObstacleType, PrizeType, NodeId},
    1: {NodeId, NodeId, ObstacleType, ObstacleType, NodeId},
    ...
  }
*/
int main() {
}