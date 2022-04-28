#include "SearchAlgos.h"
#include <stack>
#include <map>
#include <deque>

std::vector<ID> SearchAlgos::BreadthFirstSearch(ID start, ID target)
{
    std::vector<bool> visited(adjList.size(), false);
    std::deque<ID> stack;
    std::vector<ID> path;

    stack.push_back(start);

    while (!stack.empty())
    {
        ID s = stack.back();
        if (s == target)
            return path;

        stack.pop_front();

        if (!visited[s])
        {
            path.push_back(s);
            //std::cout << s << " ";
            visited[s] = true;
        }

        for (auto i = adjList[s].begin(); i != adjList[s].end(); ++i)
        {
            if (!visited[(*i).first])
                stack.push_back((*i).first);
        }
    }
    return {};
}

std::vector<ID> SearchAlgos::DepthFirstSearch(ID start, ID target)
{
    std::vector<bool> visited(adjList.size(), false);
    std::stack<ID> stack;
    std::vector<ID> path;

    stack.push(start);

    while (!stack.empty())
    {
        ID s = stack.top();
        if (s == target)
            return path;

        stack.pop();

        if (!visited[s])
        {
            path.push_back(s);
            //std::cout << s << " ";
            visited[s] = true;
        }

        for (auto i = adjList[s].begin(); i != adjList[s].end(); ++i)
        {
            if (!visited[(*i).first])
                stack.push((*i).first);
        }
    }
    return {};
}