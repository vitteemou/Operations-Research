#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

struct Edge 
{
	int start_vertex;
	int end_vertex;
	int weight;

	Edge(int s, int e, int w): start_vertex(s), end_vertex(e), weight(w) {}
};

//implementation of Karp's Minimum Mean Cycle algorithm
double minimumMeanCycle(int n, vector<vector<int>> &adj_matrix)
{
	vector<vector<int>> distances(n + 1, vector<int>(n, INT_MAX));
	distances[0][0] = 0;

	for (int k = 0; k < n; ++k)
	{ 
		for (int u = 0; u < n; ++u)
		{ 
			for (auto e: adj_matrix[u])
			{ 
				distances[k+1][e.end_vertex] = min(distances[k + 1][e.end_vertex], 
								distances[k][e.start_vertex] + e.weight);
			}
		}
	}
	int num = 1;
	int delta = 0;

	for (int k = 0; k < n; ++k)
	{ 
		for (int u = 0; u < n; ++u)
		{ 
			if (distances[k][u] < INT_MAX)
			{
				if (num * (n - k) > (distances[n][u] - distances[k][u]) * delta) 
				{
					num = (distances[n][u] - distances[k][u]);
					delta = n - k;
				}
			}
		}
	}
	return 1.0 * num / delta;
}

int main() 
{
	int n;
	cin >> n;

	vector<Edge> edges;
	vector<vector<Edge>> adj_matrix(n, vector<int>(n));

	for (int i = 0; i < n; ++i) 
	{
		for (int j = 0; j < n; ++j) 
		{  
			int weight;
			cin >> weight;

                        if(weight)
			{
				edges.push_back(new Edge(i, j, weight));
			}
			else
			{
				edges.push_back(new Edge(i, j, INT_MAX));
			}
		}
	}
	for (auto e: edges)
	{
		adj_matrix[e.start_vertex].push_back(e);
	}
        cout << minimumMeanCycle(n, adj_matrix) << endl;
}
