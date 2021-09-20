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

void graph::toplogical_sort_utill(int vertex, vector<int>& visited, stack<int>& explored_stack)const
{
	//base conditon (i.e. add vertex to stack and exit)
	//all of this vertex neighbours had been visited
	//or this vertex has no neighbours.
	
	visited[vertex] = 1;
	for (auto child:edges[vertex])
	{
		if (visited[child.to]==2)continue;
		if (visited[child.to] == 1){
		//child & child.to edge forms cycle
		//toplogical sort dose't exist
			continue;
		}
		toplogical_sort_utill(child.to, visited, explored_stack);
	}
	explored_stack.push(vertex);
	visited[vertex] = 2;
}

/*for DAG 
foreach directed edge u to v : u should come before v.
 no unique solution
*/
vector<int> graph::toplogical_sort()const
{
	stack<int> ans;//or use array and reverse it in the end;

	//0 -> not vistewd at all
	//1 -> visited it but haven't visited all vertices in its subtree
	//2 -> visited it and visited all vertices in its subtree and left it
	//ref http://codeforces.com/blog/entry/4907

	vector<int>visited(vertices_count, 0 );
	for (int i = 0; i < vertices_count; i++)
	{
		if (!visited[i])
		{
			toplogical_sort_utill(i, visited, ans);
		}
	}
	vector<int> v;
	while (!ans.empty())
	{
		v.push_back(ans.top());
		ans.pop();
	}
	return v;
}
