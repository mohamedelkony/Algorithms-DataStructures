#include <limits>
#include <vector>
#include <string>
#include <array>
#include <new>
#include <stack>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;
#define pnt_xy pair<int, int>
void dfs_scc_grid(int w, int h, pnt_xy at, vector<vector<int>> &low, vector<vector<int>> &ids, int &scc_count, int &id, stack<pnt_xy> &stk, vector<vector<bool>> &on_stack)
{
    //dfs is guranted to be called only on unvivsted nodes
    stk.push(at);
    int x = at.first;
    int y = at.second;
    on_stack[y][x] = true;
    ids[y][x] = low[y][x] = id++;

    vector<pnt_xy> edgs;
    //generate edges here:
    /*
	int x1, y1;
	if (hss[at.second] == '>')
		x1 = at.first + 1;
	else
		x1 = at.first - 1;
	if (wss[at.first] == 'v')
		y1 = at.second + 1;
	else
		y1 = at.second - 1;
	if (x1 >= 0 && x1 < w)
		edgs.push_back({ x1, at.second });
	if (y1 >= 0 && y1 < h)
		edgs.push_back({ at.first, y1 });
	*/
    for (pnt_xy to : edgs)
    {
        //Case1(Tree Edge) : If node to is not visited already, then after DFS of to is complete
        //then minimum of low[at] and low[to] will be updated to low[at].
        if (ids[to.second][to.first] == -1)
        {
            dfs_scc_grid(w, h, to, low, ids, scc_count, id, stk, on_stack);
            low[at.second][at.first] = std::min(low[to.second][to.first], low[at.second][at.first]);
        }
        //Case 2 (Back Edge) : When child to is already visited
        //To make sure, we don�t consider cross edges, when we reach a node which is already visited
        //we should process the visited node only if it is present in stack
        else if (on_stack[to.second][to.first])
        {
            low[at.second][at.first] = std::min(ids[to.second][to.first], low[at.second][at.first]);
        }
    }

    if (ids[y][x] == low[y][x])
    {
        pnt_xy c;
        //contents of stack are nodes of a strong connected component
        while (stk.top() != at)
        {
            c = stk.top();
            ///	cout << c.first << "," << c.second << " ";
            on_stack[c.second][c.first] = false;
            stk.pop();
        }
        c = stk.top();
        //	cout << c.first << ", " << c.second << "\n";
        on_stack[c.second][c.first] = false;
        stk.pop();
        scc_count++;
    }
}

void dfs_scc(int n, vector<vector<int>> &edgs, int at, vector<int> &low, vector<int> &ids, int &scc_count, int &id, stack<int> &stk, vector<bool> &on_stack)
{
    //dfs is guranted to be called only on unvivsted nodes
    stk.push(at);
    on_stack[at] = true;
    ids[at] = low[at] = id++;

    for (int to : edgs[at])
    {
        if (ids[to] == -1)
        {
            dfs_scc(n, edgs, to, low, ids, scc_count, id, stk, on_stack);
            low[at] = std::min(low[to], low[at]);
        }
        else if (on_stack[to])
        {
            low[at] = std::min(ids[to], low[at]);
        }
    }

    if (ids[at] == low[at])
    {
        int top;
        while (stk.top() != at)
        {
            top = stk.top();
            on_stack[top] = false;
            stk.pop();
        }
        top = stk.top();
        on_stack[top] = false;
        stk.pop();
        scc_count++;
    }
}
//for directed graph
//O(V+E)
int strongly_connected_compnents(int count, vector<vector<int>> edgs)
{
    vector<int> ids(count, -1);
    vector<int> low(count, -1);
    vector<bool> on_stack(count, false);
    int scc_count = 0;
    int id = 0;
    stack<int> stk;

    for (int i = 0; i < count; i++)
    {
        if (ids[i] == -1 /*not vivsted*/)
            dfs_scc(count, edgs, i, low, ids, scc_count, id, stk, on_stack);
    }
    return scc_count;
}
