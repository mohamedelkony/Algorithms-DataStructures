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
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;
vector<int> dsu_ids;
vector<int> dsu_size;
int dsu_compnents;
void initilize_dsu(int n)
{
    for (int i = 0; i < n; i++)
    {
        dsu_ids.push_back(i);
        dsu_size.push_back(1);
    }
    dsu_compnents = n;
}
int dsu_find(int id)
{
    int root = id;
    while (root != dsu_ids[root])
    {
        root = dsu_ids[root];
    }
    //path comperssion
    while (root != id)
    {
        int next = dsu_ids[id];
        dsu_ids[id] = root;
        id = next;
    }
    return root;
}
void unify(int id1, int id2)
{
    int root1 = dsu_find(id1);
    int root2 = dsu_find(id2);

    if (root1 == root2)
        return;
    //Union by size
    if (dsu_size[root1] > dsu_size[root2])
    {
        dsu_size[root1] += dsu_size[root2];
        dsu_ids[root2] = root1;
    }
    else
    {
        dsu_size[root2] += dsu_size[root1];
        dsu_ids[root1] = root2;
    }
    dsu_compnents--;
}
