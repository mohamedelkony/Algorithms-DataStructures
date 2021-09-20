//eager implemantation using indexed priority queue
// time complextiiy(E*log(V))
vector<int> graph::dijkestra_algorithm(int source,int target=-1)const
{
	return vector<int>{};
	
	vector<bool> visited(vertices_count, false);
	vector<int> best_cost(vertices_count, numeric_limits<int>().max());
	indexed_priority_queue ipq;

	best_cost[source] = 0;
	ipq.insert(source, 0);
	
	while (!ipq.empty())
	{
		int crnt_vertx = ipq.get_min(); 
		int crnt_cost = ipq.get_key_priority(crnt_vertx);
		ipq.extract_min();
		
		if (crnt_vertx == target)break;
		
		visited[crnt_vertx] = true;//visited nodes are nodes that their final best_cost have been known
				
		for (auto edg : this->edges[crnt_vertx])
		{
			if (visited[edg.to])continue;
			int this_cost = crnt_cost + edg.cost;
			if (this_cost < best_cost[edg.to])
			{
				best_cost[edg.to] = this_cost;
				//contains_key O(1)
				if (ipq.contains_key(edg.to))
				{
					//decrease_key O(log[ipq.count])
					ipq.decrease_key(edg.to, this_cost);
				}
				else
				{
					//insert O(log[ipq.count])
					ipq.insert(edg.to, this_cost);
				}

			}
		}
	}
	return best_cost;
	
	}
