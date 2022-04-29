#include "APathy.h"

struct Edge {
	int src, dest, weight;
};

int main() {
  std::vector<Edge> edges = {
    {0, 1, 6}, {1, 2, 7}, {2, 0, 5}, {2, 1, 4}, {3, 2, 10}, {5, 4, 1}, {4, 5, 3}
  };
  APathy<Edge, int, int> finder(edges, 6);

  std::vector<int> sp = finder.Dijkstra(3, 1);
  std::cout << "Found path: [ ";
  for (int i : sp)
    std::cout << i << ' ';
  std::cout << "]\n";
}
