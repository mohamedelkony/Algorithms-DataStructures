#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <array>
#include <new>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <sstream>
#include <iomanip>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

//for all graphs
//warning: fuction dosent check if all vetrices are connected(no isolated graphs)! but
//when used in finding euler path this condtion is eaiser to be checked there.
bool has_euler_path(vector<int> &in, vector<int> &out)
{
    int odd_count = 0;
    for (int i = 0; i < in.size(); i++)
    {
        int diff = abs(in[i] - out[i]);
        if (diff == 1)
            odd_count++;
        else if (diff > 1)
            return false;
    }
    if (odd_count == 0 || odd_count == 2)
        return true;
    return false;
}
void dfs_euler(int at, vector<vector<int>> &edges, vector<int> in, vector<int> &out, list<int> &path)
{
    while (out[at] != 0)
    {
        dfs_euler(edges[at][--out[at]], edges, in, out, path);
    }
    path.push_front(at);
}

//for all graphs
list<int> euler_path(vector<vector<int>> &edges)
{
    int n = edges.size();
    vector<int> in(n, 0);
    vector<int> out(n, 0);
    list<int> path;
    int edges_count = 0;

    //fill number of in & out edges for each vertex
    for (int at = 0; at < n; at++)
    {
        for (int to : edges[at])
        {
            edges_count++;
            out[at]++;
            in[to]++;
        }
    }

    if (!has_euler_path(in, out))
        return list<int>();

    //get first node to start from. any node is valid except if
    //node is isolated i.e. has no incoming or outgoing edges [graph is still euler] or
    //when graph has vertex with (in - out) edges=1 then path must start from that vertex.
    int first_vertex = -1;
    for (int i = 0; i < n; i++)
    {
        if (out[i] - in[i] == 1)
        {
            first_vertex = i;
            break;
        }
        if (out[i] > 0)
            first_vertex = i;
    }

    dfs_euler(first_vertex, edges, in, out, path);

    if (path.size() == edges_count + 1)
        return path;
    return list<int>{};
}
