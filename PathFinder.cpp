#include "PathFinder.h"
#include <set>
#include <map>
#include <algorithm>

// template<typename G, typename UID>
// 	requires GraphLike(G) && UniqueID(UID)
// std::vector<Edge> AStar(G &graph, UID start, UID end) {}

std::vector<int> PathFinder::AStar(Graph &graph, int start, int end) {
// std::vector<ID> PathFinder::AStar(Graph &graph, ID start, ID end) {
	std::vector<int> reconstructedPath;
	// std::vector<ID> reconstructedPath;
	std::set<int> openSet {start};
	std::set<int> closedSet;

	std::map<int, int> g;
	std::map<int, int> parents;
	g[start] = 0;
	parents[start] = start;

	while (openSet.size() > 0) {
		int n = -1;
		for (int v : openSet) {
			if (n == -1 || (g[v] + 1 /* heuristic [v] */ < g[n] + 1 /* heuristic [n] */ )) {
				n = v;
			}
		}

		if (n == -1) {
			return reconstructedPath;
		}
		if (n == end) {
			while (parents[n] != n) {
				reconstructedPath.push_back(n);
				n = parents[n];
			}
			reconstructedPath.push_back(start);
			std::reverse(reconstructedPath.begin(), reconstructedPath.end());
			return reconstructedPath;
		}
		for (auto pair : graph.adjList[n]) {
			int m = pair.first;
			int weight = pair.second;
			if (std::find(openSet.begin(), openSet.end(), m) == openSet.end() ||
					std::find(closedSet.begin(), openSet.end(), m) == closedSet.end()) {
				openSet.insert(m);
				parents[m] = n;
				g[m] = g[n] + weight;
			} else {
				if (g[m] > (g[n] + weight)) {
					g[m] = g[n] + weight;
					parents[m] = n;

					if (std::find(closedSet.begin(), closedSet.end(), m) != closedSet.end()) {
						closedSet.erase(m);
						openSet.insert(m);
					}
				}
			}
		}
		openSet.erase(n);
		closedSet.insert(n);
	}

	return reconstructedPath;
}