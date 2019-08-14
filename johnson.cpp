


// define minheap//
const int vsize = 100;
const int64_t posinf = 1000000000;



int64_t w[vsize][vsize], wt[vsize][vsize], l[vsize][vsize];
int h[vsize];
int d[vsize];
int vset[vsize];


// bellman-ford for single-point shortest path
void bellmanford(int s,int n)
{
	for(int i = 0;i < n;i++){h[i] = posinf;}
	h[s] = 0;

	for(int k = 0;k < n;k++)
	{
		for(int i = 0;i < n;i++)
		{
			for(int j = 0;j < n;j++)
			{
				if(h[j] > h[i]+w[i][j]){h[j] = h[i]+w[i][j];}
			}
		}
	}
}


// dijkstra for single-points shortest path with positive weights
void dijkstra(int s,int n)
{
	for(int i = 0;i < n;i++){d[i] = posinf;vset[i] = 0;}
	d[s] = 0;

	minheap.push(s);
	while(minheap.size())
	{
		while(vset[minheap.top()] == 1){minheap.pop();}
		int top = minheap.top(); minheap.pop();
		vset[top] = 1;

		for(int j = 0;j < n;j++)
		{
			if(d[j] > d[top]+wt[top][j])
			{
				d[j] = d[top]+wt[top][j];
				minheap.push(j);
			}
		}
	}
}

// johnson for all pair shortest path
void johnson(int n)
{
	// all point n, with edge n-i to all points
	for(int j = 0;j < n;j++)
	{
		w[n][j] = 0;
		w[j][n] = posinf;
	}

	// convert all weights to positive weights
	bellmanford(n, n+1);  // using weights w, and h as d
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			wt[i][j] = w[i][j]+h[j]-h[i];	 // using inequality h[u] <= h[v]+w[u][v]
		}
	}

	// now all weights are positive, run dijkstra from all points
	for(int i = 0;i < n;i++)
	{
		dijkstra(i, n);
		for(int j = 0;j < n;j++){wt[i][j] = d[j];}
	}

	// convert weights according to original weights
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			w[i][j] = wt[i][j]+h[i]-h[j]; 
		}
	}
	
}