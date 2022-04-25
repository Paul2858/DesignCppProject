template <typename T, typename W>

struct Edge
{
    T src, dest;
    W weight;
};

template <typename T, typename W>

class Graph
{
private:
    int graphSize;
    std::vector<T> nodeArray;
    std::vector<Edge> edgeArray;
    void addEdge(T node1, T node2);
    void deleteEdge(T node1, T node2);

public:
    void BFS(T Start);
    void DFS(T Start);
    void Dijkstra(T s, T t, int (*func)(W, W));
    void AStar(T s, T t, int (*func)(W, W));
    void displayGraph();
};
