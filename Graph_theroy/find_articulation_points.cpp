#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <new>
#include <cassert>
#include <memory>
#include <sstream>
#include <iomanip>
#include <list>
#include <fstream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include "graph_class.cpp"
using namespace std;

void graph::ap_dfs(int root, int at, int parent, vector<bool> &visited, vector<int> &ids, vector<int> &low, vector<int> &ans, int &out_edges_of_root) const
{
    /*
	*low:lowest id node can reach from another path exculding the path it was discoverd from
	*initialze visited and low with nnumber of discover
	*Don't skip vivsted so,we indicate reahing them from another parent(way)
	*so we updated lowest id parent can reach.
	*/
    static int id = 0;
    visited[at] = true;
    ids[at] = low[at] = id++;
    if (root == parent)
        out_edges_of_root++;
    for (auto i : edges[at])
    {
        int to = i.to;
        //don't dicover the path it came from
        if (to == parent)
            continue;

        if (visited[to])
        {
            //to was reached second time via onther path
            low[at] = std::min(low[at], ids[to]);
        }
        else
        {
            graph::ap_dfs(root, to, at, visited, ids, low, ans, out_edges_of_root);
            //after finishing [to] has a its final low value
            //so update value of parent e.g. at
            low[at] = std::min(low[at], low[to]);
            //== in case of cycle (and not part of bridge)
            //< in case of part of bridge(it will be part of cycle also)
            if (ids[at] <= low[to])
                ans[at] = true;
        }
    }
}

//O(V+E)
//for undirected & directed graphs
vector<int> graph::articulation_points() const
{
    vector<bool> visited(this->vertices_count);
    vector<int> ans(this->vertices_count);
    vector<int> low(this->vertices_count), id(this->vertices_count);

    for (int i = 0; i < vertices_count; i++)
    {
        int out_edges_of_root = 0;
        if (!visited[i])
        {
            ap_dfs(i, i, -1, visited, id, low, ans, out_edges_of_root);
            ans[i] = (out_edges_of_root > 1);
        }
    }

    return ans;
}
