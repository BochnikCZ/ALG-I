#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <unordered_set>

using std::vector, std::unordered_map, std::stack, std::unordered_set, std::cout;

struct Graph
{
    unordered_map<int, vector<int>> adj_list;
};

void dFS(const Graph &graph, int starting_point)
{
    stack<int> my_stack;
    unordered_set<int> visited; // mnozina intu pry

    my_stack.push(starting_point);
    visited.insert(starting_point);

    //cout << ;

    while (not my_stack.empty())
    {
        int current = my_stack.top();
        my_stack.pop();

        vector<int> neighbours = graph.adj_list.at(current);
        for (int neighbour : neighbours)
        {
            if (visited.find(neighbour) == visited.end())
            {
                my_stack.push(neighbour);
                visited.insert(neighbour);
            }
        }
    }
}

int main()
{
    Graph g;

    g.adj_list[0] = {1, 2};
    g.adj_list[1] = {2, 3};
    g.adj_list[2] = {1, 0};
    g.adj_list[2].push_back(3);
    g.adj_list[3] = {2, 4};
    g.adj_list[4] = {3};
    dFS(g, 0);

    return 0;
}
