#include "Graph.h"
#include "PathFinder.h"

int main() {
  std::vector<Edge> edges = {
    // (x, y, w) —> edge from `x` to `y` having weight `w`
    {0, 1, 6}, {1, 2, 7}, {2, 0, 5}, {2, 1, 4}, {3, 2, 10}, {5, 4, 1}, {4, 5, 3}
  };
  int s = (int) edges.size();
  Graph graph(edges, s);

  std::vector<int> sp = PathFinder::AStar(graph, 3, 1);
  std::cout << "Found path: [ ";
  for (int i : sp)
    std::cout << i << ' ';
  std::cout << "]\n";
}