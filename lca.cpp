
// lsa on tree

// define queue - que
// define graph


const int vsize = 100;
int par[vsize][20];
int hei[vsize];
int n;


// run dfs to set heights, and parents
void dfs(int root)
{
	que.push(root);
	while(que.size())
	{
		int u = que.front();que.pop();
		hei[u] = hei[par[u][0]]+1;
		for(int i = graph.V[u].p;i < graph.V[u].r;i++)
		{
			int v = graph.E[i].v;
			if(par[v][0] == 0){que.push(v);par[v][0] = u;}
		}
	}
}


// set parent with hops as (1<<s)
void parh()
{
	for(int s = 1;(1<<s) < n;s++)
	{
		for(int i = 1;i <= n;i++)
		{
			par[i][s] = par[par[i][s-1]][s-1];
		}
	}
}


// find parent of u at height h
int ath(int u,int h)
{
	while(hei[u] > h)
	{
		// find lowest l, such that parent of u at height diff (1<<l) is below h
		int l = 0;
		while((1<<l) < n && hei[par[u][l]] > h){l++;}

		if(hei[par[u][l]] == h){u = par[u][l];}
		else{u = par[u][l-1];}
	}

	return u;
}


// find lowest common ancesstor of u and v
int lca(int u,int v)
{
	int h = min(hei[u],hei[v]);
	u = ath(u, h);
	v = ath(v, h);

	int p = 0;
	int r = h+1;
	while(r-p > 1)
	{
		int q = (p+r)/2;
		if(ath(u, q) == ath(v, q)){p = q;}
		else{r = q;}
	}

	u = ath(u, p);
	return u;
}