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

void graph::bridges_dfs(int at, int parent, vector<bool>& visited, vector<int>& ids, vector<int>& low,vector<pair<int,int>>& ans)const
{
	/*
	*low:lowest id that node could reach from another path exculding the path it was discoverd from
	*initialze visited and low with time of discover
	*Don't skip visited so,we indicate reaching them from another parent(way)
	*so we update the lowest id that parent can reach.
	*/

	static int id=0;
	visited[at] = true; ids[at] = low[at]=id++;
	
	for (auto i : edges[at])
	{
		int to = i.to;
		//don't dicover the path it came from 
		if (to == parent)continue;

		if (visited[to])
		{
			//node to was reached second time via another path
			low[at] = std::min(low[at], ids[to]);
		}
	    else
		{
			graph::bridges_dfs(to, at, visited, ids, low,ans);
			//after finishing [to] has a its final low value
			//so update value of parent e.g. at 
			low[at] = std::min(low[at], low[to]);
			if (low[to] >ids[at])
				ans.push_back({ at, to });
		}
	}
}
//source https://www.youtube.com/watch?v=aZXi1unBdJA

//O(V+E)
//for undirected & directed graphs
vector<pair<int,int>> graph::bridges()const
{
	vector<bool> visited(this->vertices_count);
	vector<pair<int, int>> ans;
	vector<int> low(this->vertices_count),id(this->vertices_count);
	
	for (int i = 0; i < vertices_count; i++)
	{
		if (!visited[i])
		{
			bridges_dfs(i, -1, visited, id, low,ans);			
		}
	}

	return ans;
}
