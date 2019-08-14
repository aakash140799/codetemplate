


// define int64_t for matrix values//
const int limiter = 1;
const int vsize = 100;

int64_t a[vsize][vsize], b[vsize][vsize], c[vsize][vsize];
thread ithread[vsize], kthread[vsize*vsize];


// parallel vector dot product of a[i][p->r] and b[p->r][k] 
void vectordot(int i,int k,int p,int r,int64_t *s)
{
	if(r-p > limiter)
	{
		int q = (p+r)/2;

		int64_t s1, s2;
		thread first(vectordot, i, k, p, q, &s1);
		vectordot(i, k, q, r, &s2);

		first.join();
		*s = s1+s2;
	}
	else
	{
		*s = 0;
		for(int j = p;j < r;j++)
		{
			*s += a[i][j]*b[j][k];
		}
	}
}

// loop func for column
void matrixk(int i,int n)
{
	for(int k = 0;k < n;k++)
	{
		kthread[i*n +k] = thread(vectordot, i, k, 0, n, &c[i][k]);
	}
	for(int k = 0;k < n;k++)
	{
		kthread[i*n +k].join();
	}
}


// loop func for row;
void matrixi(int n)
{
	for(int i = 0;i < n;i++)
	{
		ithread[i] = thread(matrixk,i,n);
	}
	for(int i = 0;i < n;i++)
	{
		ithread[i].join();
	}
}