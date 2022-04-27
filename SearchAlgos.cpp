#include "SearchAlgos.h"
#include <stack>
#include <map>
#include <deque>

void SearchAlgos::BreadthFirstSearch(Graph &graph, int start)
{
    std::vector<bool> visited(graph.adjList.size(), false);
    std::deque<int> stack;
    stack.push_back(start);

    while (!stack.empty())
    {
        int s = stack.back();
        stack.pop_front();

        if (!visited[s])
        {
            std::cout << s << " ";
            visited[s] = true;
        }

        for (auto i = graph.adjList[s].begin(); i != graph.adjList[s].end(); ++i)
        {
            if (!visited[(*i).first])
                stack.push_back((*i).first);
        }
    }
}

void SearchAlgos::DepthFirstSearch(Graph &graph, int start)
{
    std::vector<bool> visited(graph.adjList.size(), false);
    std::stack<int> stack;
    stack.push(start);

    while (!stack.empty())
    {
        int s = stack.top();
        stack.pop();

        if (!visited[s])
        {
            std::cout << s << " ";
            visited[s] = true;
        }

        for (auto i = graph.adjList[s].begin(); i != graph.adjList[s].end(); ++i)
        {
            if (!visited[(*i).first])
                stack.push((*i).first);
        }
    }
}