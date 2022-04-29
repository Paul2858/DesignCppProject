#include "APathy.h"

#include "APathy.h"
#include <concepts>
#include <string>
#include <iostream>

int GLOBAL_ID = 0;

class Movie {
public:
  std::string title;
  int id;
  Movie(std::string t) :title(t) {
    id = GLOBAL_ID++;
  };
  // ... other movie metadata
  bool operator==(const Movie &vs) const {
    if (vs.id == this->id) {
      return true;
    } else {
      return false;
    }
  }
};
std::ostream& operator<<(std::ostream& os, const Movie& m) {
  os << m.title;
  return os;
};

struct Similarity {
  float pct;
  // float zero = 0;
  // ... other ML-like user data
  auto operator<=>(const Similarity&) const = default;
};
bool operator> (const Similarity &s1, const Similarity &s2) {
  return s1.pct < s2.pct;
};

// Similarity basicHeuristic(Movie m) {
float basicHeuristic(Movie m) {
  // return {0};
  return 0;
}

int main() {
  struct MovieEdge {
    Movie src, dest;
    // Similarity weight;
    float weight;
  };
  Movie JP {"Jurrasic Park"};
  Movie T {"Titanic"};
  Movie C {"Coda"};
  Movie HP {"Harry Potter"};
  Movie AV {"Avengers"};
  std::vector<Movie> movies = {
    
  };
  std::vector<MovieEdge> edges = {
    {movies[0], movies[1], 0.2},
    {movies[0], movies[3], 0.95},
    {movies[1], movies[4], 0.15},
    {movies[3], movies[4], 0.85}
  };

  Movie A = movies[0];
  Movie F = movies[4];

  APathy<MovieEdge, Movie, float> finder(edges, movies.size());;
  // std::vector<Movie> sp = finder.Dijkstra(A, F);

  // std::cout << "Dijkstra found path: [ ";
  // for (auto i : sp)
  //   std::cout << i << ' ';
  // std::cout << "]\n";

  std::vector<Movie> sp = finder.AStar(A, F, &basicHeuristic);

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