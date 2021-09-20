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
//#include"indexed_priority_queue.h"
#include<cstdlib>
#define pnt_xy pair<int,int>
using namespace std;

class graph
{
	struct edge
	{
		int to; int cost;
		edge(int _to, int _cost = 0) :to{ _to }, cost{ _cost }{}
		edge();
		edge(initializer_list<int> l) :to{ *l.begin() }, cost{ *(l.begin() + 1) }{}
	};

	int vertices_count;
	vector<vector<edge>> edges;
	bool directed;
	
	void DFS_util(int, vector<bool>&)const;

	void toplogical_sort_utill(int, vector<int>&, stack<int>&)const;
	void bridges_dfs(int at, int parent, vector<bool>& visited, vector<int>& ids, vector<int>& low, vector<pair<int, int>>& ans)const;
	void ap_dfs(int root,int at, int parent, vector<bool>& visited, vector<int>& ids, vector<int>& low, vector<int>& ans,int& out_edges_of_root)const;

public:
	
	graph(int n, bool _directed ) :vertices_count{ n }{
		edges = vector<vector<edge>>(vertices_count, vector<edge>{});
		directed = _directed;
	}

	
	//copy constructor
	graph(const graph& ref) : vertices_count{ ref.vertices_count }
	{
		this->directed = ref.directed;
		this->edges = vector<vector<edge>>(vertices_count);
		for (int i = 0; i < vertices_count; i++)
		{
			//memcpy(edges + i, ref.edges + i, sizeof(ref.edges + i));
			for (edge e : ref.edges[i])
			{
				this->edges[i].push_back(e);
			}
		}
	}
/*
	//copy assignment
	graph& operator=(const graph& ref) 
	{
		delete edges;

		this->directed = ref.directed;
		this->vertices_count = ref.vertices_count;

		this->edges = new vector<edge>[vertices_count]{};
		for (int i = 0; i < vertices_count; i++)
		{
			//memcpy(edges + i, ref.edges + i, sizeof(ref.edges + i));
			for (edge e : ref.edges[i])
			{
				this->edges[i].push_back(e);
			}
		}
		return *this;
	}
	//move constructor
	graph(graph&& ref) :vertices_count{ref.vertices_count}
	{
		this->directed = ref.directed;
		this->edges = ref.edges;
		ref.edges = nullptr;
	}
	//move assignment
	graph& operator=(graph&& ref)
	{
		this->directed = ref.directed;
		vertices_count = ref.vertices_count;
		this->edges = ref.edges;
		ref.edges = nullptr;
		
		return *this;
	}
	int size()const
	{
		return vertices_count;
	}
	vector<edge>& operator[](int i)
	{
		return edges[i];
	}
	~graph()
	{
		if (edges)
			delete[] edges;
	}
*/
	void add_edge(int, int, int);
	void print()const;
	
	void DFS(int)const;
	void DFS_iterative(int)const;
	vector<vector<int>> breadth_first_search(int, vector<int>&)const;
	vector<int> shortest_unweighted_path(int, int)const;
	static vector <pair<int,int>>maze_solver(vector < vector<char>> maze, pair<int, int> start, pair<int, int>end);
	vector<int> toplogical_sort()const;
	vector<int> lazy_dijkstra_algorithm(int source, int target, vector<int>& path );
	vector<int> dijkestra_algorithm(int source, int target ) const;
	vector<pair<int, int>> bridges()const;
	vector<int> articulation_points()const;
	
};

void graph::add_edge(int from, int to, int cost=0)
{
	edges[from].push_back({ to, cost });
	if (!directed)
		edges[to].push_back({ from, cost });
}

void graph::print()const
{
	for (int i = 0; i < vertices_count; i++)
	{
		cout << i << " -> [";
		for (int k = 0; k < edges[i].size(); k++)
			cout << edges[i][k].to <<", ";
		cout <<  "]"<<endl;
	}
}
