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

void graph::DFS_util(int from, vector<bool>& visited) const
{
	if (visited[from])return;
	visited[from] = true;
	cout << from<<" -> ";
	for (auto edg : edges[from])
	{
		DFS_util(edg.to, visited);
	}
}
void graph::DFS(int from)const
{
	vector<bool>visited(this->vertices_count);
	DFS_util(from, visited);
}
void graph::DFS_iterative(int source) const
{
	stack<int> s;
	s.push(source);
	vector<bool>visited(vertices_count,false);
	while (!s.empty())
	{
		int vertex = s.top(); s.pop();
		if (visited[vertex])continue;
		visited[vertex] = true;
		cout << vertex << " -> ";
		auto node_edegs = edges[vertex];
		for (auto edg : node_edegs)
		{
			s.push(edg.to);
		}
	}
}
