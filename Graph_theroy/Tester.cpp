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
#include "graph_class.cpp"
#include <cstdlib>
#include "find_eular_path.cpp"
#include "Strongly_connected_components.cpp"
#include "minimum_spanning_tree.cpp"
#include "DSU.cpp"

using namespace std;

int main()
{
	if (0)
		cout << "A";
	cout << "$";

	auto g = sample_fo_AP();

	cout << "1 ->add edge 2->print 3->DFS,5->BFS,6->shortest path,7->maze solver,8->toplogical sort,\
		9,10->lazy/eager dijkestra,11->birdges,12->articulation points,13->SCC,14->euler path,15 MST";
	vector<vector<int>> edgs1(8, vector<int>{});
	edgs1[0] = {1};
	edgs1[1] = {2};
	edgs1[3] = {4, 7};
	edgs1[4] = {5};
	edgs1[5] = {0, 6};
	edgs1[6] = {0, 2, 4};
	edgs1[7] = {5, 3};
	edgs1[2] = {};

	vector<vector<int>> edgs2(5, vector<int>{});
	edgs2[0] = {1};
	edgs2[1] = {3, 2};
	edgs2[3] = {4};
	edgs2[2] = {1};

	while (1)
	{

		int k;
		cin >> k;
		if (k == 0)
		{
			cout << "enter smaple number";
			int x;
			cin >> x;
			if (x == 0)
				g = sample1();
			else if (x == 1)
				g = DAG_sample();
		}
		if (k == 1)
		{
			cout << "enter vertices";
			int i, j;
			cin >> i >> j;
			g.add_edge(i, j);
		}
		else if (k == 2)
		{
			g.print();
		}
		else if (k == 3)
		{
			g.DFS(0);
		}
		else if (k == 4)
		{
			g.DFS_iterative(0);
		}
		else if (k == 5)
		{
			int i;
			cout << "enter vertex number";
			cin >> i;
			vector<int> aaa;
			auto v = g.breadth_first_search(i, aaa);
			int n = 1;
			for (auto layer : v)
			{
				cout << "layer " << n << " :";
				for (auto i : layer)
					cout << i << " -> ";
				cout << endl;
				n++;
			}
		}
		else if (k == 6)
		{
			cout << "enter from to values";
			int from, to;
			cin >> from >> to;
			auto v = g.shortest_unweighted_path(from, to);
			for (auto i : v)
				cout << i << " -> ";
			cout << endl;
			if (v.empty())
				cout << "NO path";
		}
		else if (k == 7)
		{
			solvemaze("maze2.txt");
		}
		else if (k == 8)
		{
			auto v = g.toplogical_sort();
			for (auto i : v)
				cout << i << " ->";
			cout << endl;
		}
		else if (k == 9)
		{
			vector<int> parents;
			auto v = g.lazy_dijkstra_algorithm(0, -1, parents);
			cout << "for source vertex 0 \n";
			for (int i = 0; i < v.size(); i++)
				cout << "{ " << i << "cost = " << v[i] << "}, ";
			cout << endl;
		}
		else if (k == 10)
		{
			cout << "enter from andd to";
			int f, t;
			cin >> f >> t;
			auto v = g.dijkestra_algorithm(f, t);
			cout << "for source vertex 0 \n";
			for (int i = 0; i < v.size(); i++)
				cout << "{ " << i << "cost = " << v[i] << "}, ";
			cout << endl;
		}
		else if (k == 11)
		{
			auto v = g.bridges();
			for (int i = 0; i < v.size(); i++)
				cout << "{ " << v[i].first << " ," << v[i].second << "}, ";
			cout << endl;
		}
		else if (k == 12)
		{
			auto v = g.articulation_points();
			for (int i = 0; i < v.size(); i++)
			{
				if (v[i])
					cout << i << endl;
			}
		}
		else if (k == 13)
		{
			cout << "scc=" << strongly_connected_compnents(8, edgs1) << endl;
		}
		else if (k == 14)
		{
			cout << "euler path ";
			auto path = euler_path(edgs2);
			for (int x : path)
				cout << " ->" << x;
		}
		else
		{
			int v, e;
			cin >> v >> e;
			vector<vector<wighted_edge>> g(v, vector<wighted_edge>{});
			for (int i = 0; i < e; i++)
			{
				int f, t;
				long long c;
				cin >> f >> t >> c;
				g[f - 1].push_back({t - 1, c});
				g[t - 1].push_back({f - 1, c});
			}
			cout << minimum_spanning_tree(v, g);
		}
	}
	return 0;
}

//pair.first : x value of vertex
//pair.second : y value of vertex
vector<pair<int, int>> graph::maze_solver(vector<vector<char>> maze, pair<int, int> start, pair<int, int> end)
{
	int xd[4]{0, 0, -1, 1};
	int yd[4]{1, -1, 0, 0};
	int maze_width = maze[0].size();
	int maze_hieght = maze.size();

	vector<vector<pnt_xy>> parents;

	//verteices that were reached before via other vertices
	//i.e. it's shortest path has been known
	//but their nieghbours still hasn't been added yet
	vector<vector<bool>> visited;

	for (int i = 0; i < maze_hieght; i++)
	{
		visited.push_back(vector<bool>(maze_width, false));
		parents.push_back(vector<pnt_xy>(maze_width, {-1, -1}));
	}

	queue<int> x_que, y_que;
	visited[start.second][start.first] = true;
	x_que.push(start.first);
	y_que.push(start.second);

	while (!x_que.empty())
	{
		int crnt_x = x_que.front();
		int crnt_y = y_que.front();
		if (crnt_x == end.first && crnt_y == end.second)
			break;
		y_que.pop();
		x_que.pop();
		for (int i = 0; i < 4; i++)
		{
			int adj_x = crnt_x + xd[i];
			int adj_y = crnt_y + yd[i];

			if (adj_x < 0 || adj_y < 0)
				continue;
			if (adj_x >= maze_width || adj_y >= maze_hieght)
				continue;

			if (maze[adj_y][adj_x] == '#')
				continue;

			if (!visited[adj_y][adj_x])
			{
				x_que.push(adj_x);
				y_que.push(adj_y);
				parents[adj_y][adj_x] = {crnt_x, crnt_y};
				visited[adj_y][adj_x] = true;
			}
		}
	}
	if (parents[end.second][end.first].first == -1)
		return vector<pair<int, int>>{};

	vector<pnt_xy> path;

	//iterate until reach node has no parent i.e.{-1.-1}
	//which may be the start point or dead end point
	for (pnt_xy crnt = end; crnt.first != -1; crnt = parents[crnt.second][crnt.first])
		path.push_back(crnt);

	std::reverse(path.begin(), path.end());

	if (path[0] == start)
		return path;
	return vector<pnt_xy>{};
}

vector<int> graph::shortest_unweighted_path(int from, int to) const
{
	vector<int> parnets(vertices_count, -1);
	this->breadth_first_search(from, parnets);
	vector<int> ans;
	//traget =-1 if it was the source or it has no parent (not reachable)
	for (int target = to; target != -1; target = parnets[target])
		ans.push_back(target);

	std::reverse(ans.begin(), ans.end());
	if (ans[0] == from) //when (ans[0]!= from) it's not reachable
		return ans;
	return vector<int>{};
}

struct min_priority_queue_comper
{
	bool operator()(pair<int, int> p1, pair<int, int> p2)
	{
		return p1.second > p2.second; //min heap
	}
};

void solvemaze(string s)
{
	char ch;
	vector<vector<char>> maze;
	pair<int, int> start, end;
	fstream fin(s, fstream::in);
	int row = 0;
	bool fistchar = true;
	while (fin >> noskipws >> ch)
	{
		if (ch == '\n')
		{
			row++;
			fistchar = true;
		}
		else if (fistchar)
		{
			maze.push_back(vector<char>{ch});
			fistchar = false;
		}
		else
		{
			if (ch != EOF)
			{
				maze[row].push_back(ch);
				fistchar = false;
				if (ch == 'S')
				{
					start.first = maze[row].size() - 1;
					start.second = row;
				}
				else if (ch == 'E')
				{
					end.first = maze[row].size() - 1;
					end.second = row;
				}
			}
		}
	}

	for (auto d : maze)
	{
		for (char c : d)
			cout << c;
		cout << endl;
	}
	cout << endl;

	auto ans = graph::maze_solver(maze, start, end);
	for (auto x : ans)
	{
		if (x == start || x == end)
			continue;
		maze[x.second][x.first] = '@';
	}
	for (auto d : maze)
	{
		for (char c : d)
			cout << c;
		cout << endl;
	}
	cout << endl;
}

graph DAG_sample()
{
	graph g(13, true);
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(1, 5);
	g.add_edge(2, 4);
	g.add_edge(2, 3);
	g.add_edge(5, 4);
	g.add_edge(0, 6);
	g.add_edge(6, 5);
	g.add_edge(7, 8);
	g.add_edge(7, 9);
	g.add_edge(10, 11);
	g.add_edge(10, 0);
	g.add_edge(9, 0);
	g.add_edge(10, 9);
	g.add_edge(11, 12);
	g.add_edge(11, 2);
	g.add_edge(12, 2);
	g.add_edge(8, 0);
	return g;
}
graph sample1()
{
	graph g(21, false);
	g.add_edge(0, 1);
	g.add_edge(0, 2);
	g.add_edge(0, 12);
	;
	g.add_edge(2, 15);
	g.add_edge(2, 3);
	g.add_edge(1, 17);
	g.add_edge(17, 3);
	g.add_edge(15, 16);
	g.add_edge(3, 18);
	g.add_edge(18, 4);
	g.add_edge(8, 14);
	g.add_edge(4, 5);
	g.add_edge(4, 6);
	g.add_edge(4, 7);
	g.add_edge(4, 9);
	g.add_edge(7, 8);
	g.add_edge(8, 9);
	g.add_edge(9, 10);
	g.add_edge(9, 11);
	g.add_edge(12, 13);
	g.add_edge(13, 14);
	g.add_edge(20, 19);
	g.add_edge(11, 17);
	g.add_edge(13, 18);
	g.add_edge(16, 0);
	g.add_edge(1, 15);
	g.add_edge(3, 5);
	return g;
}
graph sample_fo_AP()
{
	graph g(9, false);
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(0, 2);

	g.add_edge(2, 5);
	g.add_edge(2, 3);
	g.add_edge(3, 4);

	g.add_edge(5, 6);
	g.add_edge(6, 7);
	g.add_edge(7, 8);
	g.add_edge(5, 8);
	return g;
}
graph directed_wighted_sample1()
{
	graph g(6, true);
	g.add_edge(0, 1, 5);
	g.add_edge(0, 2, 1);
	g.add_edge(1, 3, 3);
	g.add_edge(1, 2, 2);
	g.add_edge(2, 1, 3);
	g.add_edge(1, 4, 20);
	g.add_edge(2, 4, 12);
	g.add_edge(3, 5, 6);
	g.add_edge(3, 4, 2);
	g.add_edge(3, 2, 3);
	g.add_edge(4, 5, 1);
	return g;
}

typedef unsigned long long int big_int;
typedef enum _types
{
	nlog_t,
	nsquared_t,
	n_t,
	of_one_t,
	logn_t
} types;
typedef struct _big_o
{
	int val;
	types type;
} big_o;

int time_analysis_comper(const void *p1, const void *p2)
{
	return ((big_o *)p1)->val - ((big_o *)p2)->val;
}

string big_o_tostr(big_o b)
{

	string s;
	switch (b.type)
	{
	case nlog_t:
		s = "nlogn";
		break;
	case logn_t:
		s = "logn";
		break;
	case nsquared_t:
		s = "nsquare";
		break;
	case of_one_t:
		s = "1";
		break;
	case n_t:
		s = "n";
		break;
	}
	return s;
}
void analyize_time(big_int n, big_int compares_count)
{
	/*float nsquared_cof = compares_count / (long double)(n*n);
	float nlogn_cof = compares_count / (n*log2(n));
	float n_cof = compares_count / (long double)n;
	float logn_cof = compares_count / (log2(n));
	*/
	//printf(">>>Time (%llu) complexity :%0.3f logn, %0.3f n ,%0.3f nlog2n ,%0.3f n^2\n",compares_count,logn_cof, n_cof, nlogn_cof, nsquared_cof);

	big_o o1 = {abs((long)(compares_count - (n * n))), nsquared_t};
	big_o o2 = {abs(compares_count - (n * log2(n))), nlog_t};
	big_o o3 = {abs((long)(compares_count - n)), n_t};
	big_o o4 = {abs((long)(compares_count - 1)), of_one_t};
	big_o o5 = {abs(compares_count - (log2(n))), logn_t};

	big_o os[5];
	os[0] = o1;
	os[1] = o2;
	os[2] = o3;
	os[3] = o4;
	os[4] = o5;
	qsort(os, 5, sizeof(big_o), time_analysis_comper);
	printf("%llu comparsions done for a queue of size %d\n", compares_count, n);
	printf("  >> its bestfit is O(%s),2nd bestfit is O(%s)\n\n", big_o_tostr(os[0]).c_str(), big_o_tostr(os[1]).c_str());
}
