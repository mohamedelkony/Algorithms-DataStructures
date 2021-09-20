#include <array>
#include <new>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <sstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <bitset>
#include <regex>
#include <random>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <cstdlib>
#include <functional>
using namespace std;
typedef pair<int, long long> wighted_edge;

struct edge
{
    int from, to, cost;
    edge(int f, int t, long long c) : from{f}, to{t}, cost{c} {}
};
struct mst_comper
{
    bool operator()(edge a, edge b)
    {
        return a.cost > b.cost;
    }
};
//lazy prim algorithm
//for undirected graph
//O((E+V)log(V))
int minimum_spanning_tree(int nodes_count, vector<vector<wighted_edge>> edges)
{
    int min_cost = 0;
    int edges_count = 0;
    int mst_edges_count = nodes_count - 1;
    vector<bool> visited(nodes_count, false);
    priority_queue<edge, vector<edge>, mst_comper> q; //min heap

    for (wighted_edge w : edges[0])
    {
        q.push({0, w.first, w.second});
    }
    visited[0] = true;

    while (!q.empty())
    {
        edge e = q.top();
        q.pop();
        if (visited[e.to])
            continue;
        min_cost += e.cost;
        edges_count++;
        visited[e.to] = true;
        ///	cout << "{" << e.from << "," << e.to << ":"<< e.cost << "}"<<endl;
        for (wighted_edge w : edges[e.to])
        {
            if (visited[w.first])
                continue;
            q.push({e.to, w.first, w.second});
        }
    }
    if (edges_count != nodes_count - 1)
        return -1; //mst dosen't exist due to existence of isolated components
    return min_cost;
}
