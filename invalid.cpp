#include "APathy.h"
#include <string>
#include <iostream>

// g++-11 -std=c++20 -g -Wall -O3 invalid.cpp -o invalid && ./invalid
struct Point {
  std::string id;
  int x, y;
};
std::ostream& operator<<(std::ostream& os, const Point& pt) {
  os << pt.id;
  return os;
};

float basicHeuristic(Point p) {
  return 0;
}

int main() {
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
  APathy<PointEdge, Point, float> finder(edges, 12);;
  std::vector<Point> sp = finder.Dijkstra(A, F);

  std::cout << "Dijkstra found path: [ ";
  for (auto i : sp)
    std::cout << i << ' ';
  std::cout << "]\n";

  sp = finder.AStar(A, F, &basicHeuristic);

  std::cout << "AStar found path: [ ";
  for (auto i : sp)
    std::cout << i << ' ';
  std::cout << "]\n";

  sp = finder.BreadthFirstSearch(A, F);

  std::cout << "BreadthFirstSearch found traversal: [ ";
  for (auto i : sp)
    std::cout << i << ' ';
  std::cout << "]\n";

  sp = finder.DepthFirstSearch(A, F);

  std::cout << "DepthFirstSearch found traversal: [ ";
  for (auto i : sp)
    std::cout << i << ' ';
  std::cout << "]\n";
}