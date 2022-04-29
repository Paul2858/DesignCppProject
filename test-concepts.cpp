#include "APathy.h"
#include <string>
#include <iostream>

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
struct Point {
  std::string id;
  int x, y;
  auto operator<=>(const Point&) const = default;
};
std::ostream& operator<<(std::ostream& os, const Point& pt) {
  os << pt.id;
  return os;
};

float basicHeuristic(Point p) {
  return 0;
};

int main() {
  /* EXAMPLE 1 strings as node ids */
  // struct StringEdge {
  //   std::string src, dest;
  //   int weight;
  // };
  // std::vector<StringEdge> edges = {
  //   {"0", "1", 6},
  //   {"1", "2", 7},
  //   {"2", "0", 5},
  //   {"2", "1", 4},
  //   {"3", "2", 10},
  //   {"5", "4", 1},
  //   {"4", "5", 3}
  // };

  // APathy<StringEdge, std::string, int> finder(edges, 6);
  // std::cout << "VALUES:\n";
  // finder.printVals();
  // std::cout << "ADJ LIST:\n";
  // finder.printAdjList();
  // std::vector<std::string> sp = finder.AStar("3", "1");
  // std::vector<std::string> sp = finder.BreadthFirstSearch("3", "1");
  // std::vector<std::string> sp = finder.DepthFirstSearch("3", "1");
  // std::vector<std::string> sp = finder.Dijkstra("3", "1");

  /* EXAMPLE 2 arbitrary struct as node ids */
  struct PointEdge {
    Point src, dest;
    float weight;
  };
  Point A {"A", 0, 0};
  Point B {"B", 1, 5};
  Point C {"C", 3, 1};
  Point D {"D", 2, 2};
  Point E {"E", 7, 1};
  Point F {"F", 9, 0};
  Point G {"G", 0, 8};
  Point H {"H", 3, 8};
  Point I {"I", 7, 11};
  Point J {"J", 11, 18};
  Point K {"K", 11, 17};
  Point L {"L", 4, 10};
  std::vector<PointEdge> edges = {
    {A, B, 3.0},
    {A, C, 2.0},
    {B, C, 2.0},
    {B, F, 12.0},
    {B, G, 3.0},
    {C, D, 2.0},
    {D, E, 5.0},
    {D, F, 10.0},
    {F, G, 1.0},
    {F, I, 6.0},
    {F, H, 7.0},
    {H, L, 4.0},
    {I, J, 10.0},
    {J, K, 5.0},
    {L, J, 2.0}
  };
  APathy<PointEdge, Point, float> finder(edges, 12);
  // std::cout << "VALUES:\n";
  // finder.printVals();
  // std::cout << "ADJACENCY LIST:\n";
  // finder.printAdjList();
  std::vector<Point> sp = finder.AStar(A, F, &basicHeuristic);
  // std::cout << "BFS:\n";
  // std::vector<Point> sp = finder.BreadthFirstSearch(A, F);
  // std::cout << "Found path: [ ";
  // for (auto i : sp)
  //   std::cout << i << ' ';
  // std::cout << "]\n";
  // std::cout << "DFS:\n";
  // // std::vector<Point>
  // sp = finder.DepthFirstSearch(A, F);
  // std::vector<Point> sp = finder.Dijkstra(A, F);

  /* PRINT THE SHORTEST PATH IT FOUND */
  std::cout << "Found path: [ ";
  for (auto i : sp)
    std::cout << i << ' ';
  std::cout << "]\n";
}