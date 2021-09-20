#include<iostream>
#include <limits>
#include<vector>
#include<string>
#include<array>
#include<new>
#include<cassert>
#include<stdexcept>
#include<memory>
#include<sstream>
#include<iomanip>
#include<list>
#include<algorithm>
#include<fstream>
#include<map>
#include<set>
#include<bitset>
#include<regex>
#include<random>
#include<unordered_set>
#include<unordered_map>
#include<stack>
#include<queue>
#include<cstdlib>
#include<functional>
#include<cstdlib>
#include"graph_class.cpp"

using namespace std;

//O(E*log(V))
//suits non-negative weighted grahps
vector<int> graph::lazy_dijkstra_algorithm(int source, int target, vector<int>& path )
{
	vector<bool> visited(this->vertices_count, false);
	vector<int> best_cost(this->vertices_count, numeric_limits<int>().max());
	priority_queue < pair<int, int>, vector<pair<int, int>>, min_priority_queue_comper> q;
	
	q.push({ source, 0 });
	best_cost[source] = 0;
	vector<int>parents = vector<int>(this->vertices_count, -1);
	while (!q.empty())
	{
		int crnt_node = q.top().first;
		int crnt_cost = q.top().second;
		q.pop();

		if (best_cost[crnt_node] < crnt_cost)continue;//skip duplicated outdated pairs (due to lazy implementation)
		visited[crnt_node] = true;//visited nodes are nodes that their final best_cost have been known
		if (crnt_node == target)break;

		for (auto edg : edges[crnt_node])
		{
			if (visited[edg.to])continue;
			int this_cost = best_cost[crnt_node] + edg.cost;
			if (this_cost < best_cost[edg.to])
			{
				parents[edg.to] = crnt_node;//crnt_node is a candidate best parent
				best_cost[edg.to] = this_cost;
				q.push({ edg.to, this_cost });
			}
		}
	}
	path.clear();
	if (target != -1)
	{
		if (best_cost[target] != numeric_limits<int>().max())
		{
			
			for (int prnt = target; prnt != -1; prnt = parents[prnt])
				path.push_back(prnt);
		}
		std::reverse(path.begin(), path.end());
	}
	return best_cost;
}
