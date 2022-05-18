//returns all bridges edges for every connected component in undirected/directed graph
//O(V+E)
class findBridges {
    int n;
    int[] status;
    int[] timeFoundOf;
    int[] timeFoundOfAncestorViaBackEdge;
    List<List<Integer>> bridges;
    List<List<Integer>> g;
    int time = 0;

    public findBridges(List<List<Integer>> graph) {
        this.g = graph;
        n = g.size();
        status = new int[n];
        timeFoundOf = new int[n];
        timeFoundOfAncestorViaBackEdge = new int[n];
        bridges = new ArrayList<>();
    }

    void dfs(int at, int parent) {
        status[at] = 1;
        timeFoundOf[at] = time++;
        timeFoundOfAncestorViaBackEdge[at] = timeFoundOf[at];
        for (int to : g.get(at)) {
            //dfs roots undirected graphs into a tree
            //remove this condition if graph is directed
            if (to == parent) continue;

            if (status[to] == 0) {
                dfs(to, at);
                //time of root via backward edge of to is now calculated
                timeFoundOfAncestorViaBackEdge[at] = Math.min(timeFoundOfAncestorViaBackEdge[at], timeFoundOfAncestorViaBackEdge[to]);

                if (timeFoundOf[at] < timeFoundOfAncestorViaBackEdge[to])
                    //the path [at-->to] doesn't have backward path from [to -->at]
                    //so it's a bridge
                    bridges.add(Stream.of(at, to).toList());
            } else //this edge at-->to is a backward edge
            {
                timeFoundOfAncestorViaBackEdge[at] = Math.min(timeFoundOfAncestorViaBackEdge[at], timeFoundOf[to]);
            }
        }
        status[at] = 2;
    }

    List<List<Integer>> find() {
        for (int i = 0; i < n; i++) {
            if (status[i] == 0) dfs(i, -1);
        }
        return bridges;
    }
}
