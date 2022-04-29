#include "APathy.h"
#include <concepts>
#include <string>
#include <iostream>
#include <chrono>

// g++-11 -std=c++20 -g -Wall -O3 movies.cpp -o movies && ./movies
using namespace std::chrono;
void printDuration (const duration<double>& d) {
  const auto ms = duration_cast<microseconds>(d);
  std::cout << (float) ms.count() / 1000;
}

int GLOBAL_ID = 0;

struct Movie {
  std::string title;
  int id;
  // // ... other movie metadata
  auto operator<=>(const Movie&) const = default;
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
    float weight;
  };
  Movie JP{"Jurrasic Park"};
  Movie T{"Titanic"};
  Movie C{"Coda"};
  Movie HP{"Harry Potter"};
  Movie AV{"Avengers"};
  Movie GF{"Godfather"};      //5
  Movie KB{"Kill Bill"};      // 6
  Movie SN{"Social Network"}; //7
  Movie Z{"Zodiac"};          //8
  Movie S{"Se7en"};           //9
  std::vector<Movie> movies = {
    JP, T, C, HP, AV, GF, KB, SN, Z, S
  };
  std::vector<MovieEdge> edges = {
    {movies[0], movies[1], 0.2},
    {movies[0], movies[3], 0.95},
    {movies[1], movies[4], 0.15},
    {movies[3], movies[4], 0.85},
    {movies[0], movies[5], 0.2},
    {movies[0], movies[7], 0.3},
    {movies[8], movies[9], 0.95},
    {movies[3], movies[5], 0.4},
    {movies[8], movies[7], 0.7}
  };

  auto start = high_resolution_clock::now();
  APathy<MovieEdge, Movie, float> finder(edges, movies.size());
  auto end = high_resolution_clock::now();
  duration<double> diff = end - start;
  std::cout << "Initialized *APathy* in ";
  printDuration(diff);
  std::cout << "ms\n";

  start = high_resolution_clock::now();
  std::vector<Movie> sp = finder.Dijkstra(JP, AV);
  end = high_resolution_clock::now();
  diff = end - start;

  std::cout << "Dijkstra found path: [ ";
  for (auto i : sp)
    std::cout << i << ' ';
  std::cout << "] in ";
  printDuration(diff);
  std::cout << "ms\n";

  start = high_resolution_clock::now();
  sp = finder.AStar(JP, AV, &basicHeuristic);
  end = high_resolution_clock::now();
  diff = end - start;

  std::cout << "AStar found path: [ ";
  for (auto i : sp)
    std::cout << i << ' ';
  std::cout << "] in ";
  printDuration(diff);
  std::cout << "ms\n";

  start = high_resolution_clock::now();
  sp = finder.BreadthFirstSearch(JP, AV);
  end = high_resolution_clock::now();
  diff = end - start;

  std::cout << "BreadthFirstSearch found traversal: [ ";
  for (auto i : sp)
    std::cout << i << ' ';
  std::cout << "] in ";
  printDuration(diff);
  std::cout << "ms\n";

  start = high_resolution_clock::now();
  sp = finder.DepthFirstSearch(JP, AV);
  end = high_resolution_clock::now();
  diff = end - start;

  std::cout << "DepthFirstSearch found traversal: [ ";
  for (auto i : sp)
    std::cout << i << ' ';
  std::cout << "] in ";
  printDuration(diff);
  std::cout << "ms\n";
}