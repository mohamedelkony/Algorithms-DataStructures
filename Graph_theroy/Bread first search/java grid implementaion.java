    class bfs {
        int[][] grid;
        int rows_count;
        int columns_count;

        public int shortestPathBinaryMatrix(int[][] Grid) {
            grid = Grid;
            rows_count = grid.length;
            columns_count = grid[0].length;
              if(grid[0][0]==1)
                return -1;
            return bfs(new int[]{0, 0}, new int[]{rows_count - 1, columns_count - 1});
        }

        int bfs(int[] source, int[] target) {
            var visited = new int[rows_count][];
            for (int i = 0; i < rows_count; i++)
                visited[i] = new int[columns_count];

            Queue<int[]> q = new LinkedList<int[]>();
            int next_layer_count = 0;
            int current_layer_count = 1;
            q.add(source);
            var dx = new int[]{-1, 0, 1, -1, 1, -1, 0, 1};
            var dy = new int[]{-1, -1, -1, 0, 0, 1, 1, 1};
            var layers = new Stack<List<int[]>>();
            layers.add(new ArrayList<>());
            while (!q.isEmpty()) {
                layers.peek().add(q.peek());
                var parent = q.poll();
                if (parent[0] == target[0] &&parent[1]==target[1])
                    return layers.size();
                for (int i = 0; i < 8; i++) {
                    int adjx = parent[0] + dx[i];
                    int adjy = parent[1] + dy[i];
                    if (adjx < 0 || adjx >= columns_count || adjy < 0 || adjy >= rows_count)
                        continue;
                    if (grid[adjy][adjx] == 1) continue;
                    if (visited[adjy][adjx] == 1)
                        continue;
                    q.add(new int[]{adjx, adjy});
                    visited[adjy][adjx]= 1;
                    next_layer_count++;
                }
                current_layer_count--;
                if (current_layer_count == 0) {
                    current_layer_count = next_layer_count;
                    next_layer_count = 0;
                    layers.add(new ArrayList<>());
                }
            }
            return -1;
        }
    }
