


// define graph//
// define que//


// left vertice [1-n]//
// right vertice [1-m]//
// graph.m == no.of edges, only m == no.of right vertices//
int lmatch[vsize];
int rmatch[vsize];
int parent[vsize];
int dist[vsize];

bool bfsfunc(int n,int m)
{
	// push non-matching left vertices;
	for(int i = 1; i <= n; i++)
	{
		if(lmatch[i] == 0)
		{
			que.push(i);
			dist[i] = 0;
		}
		else
		{
			dist[i] = posinf;
		}
	}


	// run bfs untill a non-matching right vertice is found
	int found = 0;
	while(que.size())
	{
		int u = que.front();
		que.pop();

		// check all edges of left vertice
		for(int i = graph.V[u].p; i < graph.V[u].r; i++)
		{
			int v = graph.E[i].v;

			// non-matching right vertice
			if(rmatch[v] == 0)
			{
				parent[v] = u;
				found = v;
				break;
			}
			// not-pushed left vertice
			else if(dist[rmatch[v]] == posinf)
			{
				parent[v] = u;
				dist[rmatch[v]] = dist[u]+1;
				que.push(rmatch[v]);
			}
		}

		// if non-match right vertice is found
		if(found != 0){break;}
	}
	// empty que
	while(que.size()){que.pop();}

	if(found != 0)
	{
		// swap non-matching edges, and matching edges
		int v = found;
		int u, t;
		while(v != 0)
		{
			u = parent[v];
			t = lmatch[u];

			lmatch[u] = v;
			rmatch[v] = u;

			v = t;
		}
	}

	return (found>0);
}

int hopcroft(int n,int m)
{
	// intial matching
	for(int i = 1; i <= n; i++)
	{
		for(int k = graph.V[i].p; k < graph.V[i].r; k++)
		{
			if(rmatch[graph.E[k].v] == 0)
			{
				lmatch[i] = graph.E[k].v;
				rmatch[graph.E[k].v] = i;
				break;
			}
		}
	}

	// while augmenting path, swap matching and non-matching edges
	while(bfsfunc(n,m)){continue;}

	// count of maximum matching
	int c = 0;
	for(int i = 1; i <= n; i++)
	{
		c += (lmatch[i]>0);
	}
	return c;
}