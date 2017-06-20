// Ford-Fulkerson

#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

bool breadthFirstSearch(int n, vector<vector<int>> &residual_graph, int s, int t, vector<int> &parent)
{
	vector<bool> visited(n, 0);
	queue <int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v = 0; v < n; v++)
		{
			if (visited[v] == false && residual_graph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	return (visited[t] == true); // reaching the sink 't'
}

// Returns the maximum flow from s to t in the given graph
int FordFulkerson(int n, vector<vector<int>> &graph, int s, int t)
{
	vector<vector<int>> residual_graph(n, vector<int>(n));
	for (int u = 0; u < n; u++)
	{
		for (int v = 0; v < n; v++)
		{
			residual_graph[u][v] = graph[u][v];
		}
	}

	vector<int> parent(n);
	int max_flow = 0;

	// Augment the flow while there is path from source to sink
	while (breadthFirstSearch(n, residual_graph, s, t, parent))
	{
		int path_flow = INT_MAX;
		int v = t;

		while(v != s)
		{
			int u = parent[v];
			path_flow = min(path_flow, residual_graph[u][v]);
			v = parent[v];
		}

		v = t;
		while(v != s)
		{
			int u = parent[v];
			residual_graph[u][v] -= path_flow;
			residual_graph[v][u] += path_flow;
			v = parent[v];
		}

		// Add path flow to overall flow
		max_flow += path_flow;
	}
	return max_flow;
}

int main()
{
	int n;
	cin>>n;

	vector<vector<int>> graph(n, vector<int>(n, 0));

	for (int i = 0; i < n; ++i) 
	{
		for (int j = 0; j < n; ++j) 
		{  
			int weight;
			cin >> weight;
			graph[i][j] = weight;
		}
	}
	cout << "Maximal flow: " << FordFulkerson(n, graph, 0, n - 1);
	return 0;
}
