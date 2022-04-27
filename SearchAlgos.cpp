#include "SearchAlgos.h"
#include <stack>
#include <map>
#include <deque>

std::vector<int> SearchAlgos::BreadthFirstSearch(Graph &graph, int start, int target)
{
    std::vector<bool> visited(graph.adjList.size(), false);
    std::deque<int> stack;
    std::vector<int> path;

    stack.push_back(start);

    while (!stack.empty())
    {
        int s = stack.back();
        if (s == target)
            return path;

        stack.pop_front();

        if (!visited[s])
        {
            path.push_back(s);
            //std::cout << s << " ";
            visited[s] = true;
        }

        for (auto i = graph.adjList[s].begin(); i != graph.adjList[s].end(); ++i)
        {
            if (!visited[(*i).first])
                stack.push_back((*i).first);
        }
    }
    return {};
}

std::vector<int> SearchAlgos::DepthFirstSearch(Graph &graph, int start, int target)
{
    std::vector<bool> visited(graph.adjList.size(), false);
    std::stack<int> stack;
    std::vector<int> path;

    stack.push(start);

    while (!stack.empty())
    {
        int s = stack.top();
        if (s == target)
            return path;

        stack.pop();

        if (!visited[s])
        {
            path.push_back(s);
            //std::cout << s << " ";
            visited[s] = true;
        }

        for (auto i = graph.adjList[s].begin(); i != graph.adjList[s].end(); ++i)
        {
            if (!visited[(*i).first])
                stack.push((*i).first);
        }
    }
    return {};
}