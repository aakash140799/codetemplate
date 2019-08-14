


const int vsize = 100;
const int64_t  posinf = 1000000000;


// edge relaxation using matrix multiplication
void extendedshortestpaths(int64_t a[vsize][vsize],int64_t b[vsize][vsize],int64_t c[vsize][vsize],int n)
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

int64_t w[vsize][vsize], l[vsize][vsize], t[vsize][vsize];
void allpairshortestpath(int n)
{
	// l is initialized to w, so that l = w0
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			l[i][j] = w[i][j];
		}
	}

	// each iteration of k relaxes edges of l, by one step;
	// after each iteration, l = wk;
	for(int k = 1;k < n;k++)
	{
		extendedshortestpaths(l,w,t,n);		// perform t = l X w, where l = w(k-1), and t becomes w(k);
		for(int i = 0;i < n;i++)
		{
			for(int j = 0;j < n;j++)
			{
				l[i][j] = t[i][j];
			}
		}
	}
}