// floyd-warshall


int l[100][100], lk[100][100];
// runs allpair shortest path algorithm: floyd warshall
void floydwarshall(int n)
{
	// iterate for 0-(n-1) vertices in path;
	for(int k = 0;k < n;k++)
	{
		// set lk by relaxing all vertices with kth vertice;
		for(int i = 0;i < n;i++)
		{
			for(int j = 1;j <= n;j++)
			{
				lk[i][j] = min(l[i][j], l[i][k]+l[k][j]);
			}
		}
		// set l to lk;
		for(int i = 0;i < n;i++)
		{
			for(int j = 0;j < n;j++)
			{
				l[i][j] = lk[i][j];
			}
		}
	}
}
