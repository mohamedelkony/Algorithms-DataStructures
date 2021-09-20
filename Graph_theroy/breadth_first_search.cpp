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


vector<vector<int>> graph::breadth_first_search(int source, vector<int>& parents )const
{
	vector<int> ans; ans.reserve(vertices_count);
	
	vector<vector<int>> layers;
	
	vector<bool> visited(vertices_count, false);
	
	visited[source] = true;
	queue<int> q;
	int vertices_left_in_layer = 1;
	int next_layer_count = 0;
	q.push(source);
	vector<int> layer;
	while (!q.empty())
	{
		int vertex = q.front(); q.pop();
		ans.push_back(vertex);
		
		if (vertices_left_in_layer == 0)
		{vertices_left_in_layer = next_layer_count; next_layer_count = 0;
		layers.push_back(layer);
		layer.clear();
		}	
		vertices_left_in_layer--;
		
		for (auto edg : this->edges[vertex])
		{
			if (!visited[edg.to])
			{
				visited[edg.to] = true;
				q.push(edg.to);
				next_layer_count++;
				layer.push_back(edg.to);
				if (!parents.empty())
					parents[edg.to] = vertex;
			}
			
		}
	}
	return layers;
}
