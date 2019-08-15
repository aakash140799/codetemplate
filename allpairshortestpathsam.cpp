


const int vsize = 100;
const int64_t posinf = 1000000000;

// edge relaxation using matrix multiplication
void extendedshortestpath(int64_t a[vsize][vsize],  int64_t b[vsize][vsize],  int64_t c[vsize][vsize],  int n)
{
	for(int i = 0;i < n;i++)
	{
		for(int k = 0;k < n;k++)
		{
			c[i][k] = posinf;
			for(int j = 0;j < n;j++)
			{
				c[i][k] = min(c[i][k], a[i][j]+b[j][k]);
			}
		}
	}
}



int64_t l[vsize][vsize], w[vsize][vsize], t[vsize][vsize];
// w[u][v] - weight of edge[u][v] if exists, else posinf
// l[u][v] - shortest path distance between (u,v) if exists, else posinf
// shortest path using matrix multiplication and , square and multiplication
void allpairshortestpathsam(int n)
{
	// initializes l to w , l = w(1);
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			l[i][j] = w[i][j];
		}
	}

	// at each iteration of p, l = w(p);
	int p = 1;
	while(p < n)
	{
		extendedshortestpath(l, l, t, n);	// sets t = l*l, and l = w(p)
		for(int i = 0;i < n;i++)
		{
			for(int j = 0;j < n;j++)
			{
				l[i][j] = t[i][j];
			}
		}
		p <<= 1;
	}
}
