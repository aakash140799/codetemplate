


const int arrsize = 100;
// linear-program defined by
// standard form
// Ax <= b;
// maximize cx
//
// slack formm
// basic[] = b - Ax
// maximize v + c * nonbasic[]
class linearprogram
{
	public:
	float A[arrsize][arrsize];
	float b[arrsize];
	float c[arrsize];
	float v;

	int basic[arrsize], nonbasic[arrsize];
	int n, m;
};

linearprogram L;
linearprogram Lt;

float del[arrsize];
float ct[arrsize];

// convert standard form to slack form
void standardtoslack(linearprogram &L)
{
	// set basic and non-basic variable count
	Lt.n = L.n;
	Lt.m = L.m;
	int n = L.n;
	int m = L.m;
	
	// place cofficients according to index in basic variables
	for(int i = 0;i < m;i++)
	{
		for(int j = 0;j < n;j++)
		{
			Lt.A[i+n][j] = L.A[i][j];
		}
	}
	for(int i = 0;i < m;i++)
	{
		Lt.b[i+n] = L.b[i];
	}
	for(int i = 0;i < n;i++)
	{
		Lt.c[i] = L.c[i];
	}
	
	// place basic and non-basic varibles index
	for(int i = 0;i < n;i++)
	{
		Lt.nonbasic[i]  = i;
	}
	for(int i = 0;i < m;i++)
	{
		Lt.basic[i] = i+n;
	}
	Lt.v = 0;

	// copy new linearprogram into orginial
	L = Lt;
}


// swap a non-basic variable e, by basic variable l
void pivot(linearprogram &L, int l,int e)
{
	// change linear equation pointed by basic variable l
	Lt.b[e] = L.b[l]/L.A[l][e];
	for(int l1 = 0; l1 < L.n; l1++)
	{
		int j = L.nonbasic[l1];
		Lt.A[e][j] = L.A[l][j]/L.A[l][e];

	}Lt.A[e][l] = 1/L.A[l][e];


	// change linear equation pointed by other basic variables
	for(int l1 = 0; l1 < L.m; l1++)
	{
		int i = L.basic[l1];

		Lt.b[i] = L.b[i] - (L.A[i][e]*Lt.b[e]);
		for(int l2 = 0; l2 < L.n; l2++)
		{
			int j = L.nonbasic[l2];
			Lt.A[i][j] = L.A[i][j] - (L.A[i][e]*Lt.A[e][j]);
		}Lt.A[i][l] = -(L.A[i][e]*Lt.A[e][l]);
	}

	// change objective function
	for(int l1 = 0; l1 < L.n; l1++)
	{
		int j = L.nonbasic[l1];
		Lt.c[j] = L.c[j] - (L.c[e]*Lt.A[e][j]);
	}Lt.c[l] = -(L.c[e]*L.A[e][l]);

	// change objective function constant
	Lt.v = L.v + (L.c[e]*Lt.b[e]);
	
	// swap l, e in basic, and non-basic array
	int li, ei;
	for(int l1 = 0; l1 < L.n; l1++)
	{
		Lt.nonbasic[l1] = L.nonbasic[l1];
		if(L.nonbasic[l1] == e){ei = l1;}
	}
	for(int l1 = 0; l1< L.m; l1++)
	{
		Lt.basic[l1] = L.basic[l1];
		if(L.basic[l1] == l){li = l1;}
	}
	swap(Lt.basic[li], Lt.nonbasic[ei]);

	// copy new linear-program into original
	L = Lt;
}

// pivot in linearprogram untill, all coficients in objective function are negative
bool basicloop(linearprogram &L)
{
	while(true)
	{
		// search for non-negative cofficient non-basic variable in objective function
		int e = -1;
		for(int l1 = 0; l1 < L.n; l1++)
		{
			int j = L.nonbasic[l1];
			if(L.c[j] > 0){e = j;break;}
		}
		// if none, exit
		if(e == -1){break;}
		
		// search for basic variable, which is most constraining
		int l = -1;
		for(int l1 = 0; l1 < L.m; l1++)
		{
			int i = L.basic[l1];
			if(L.A[i][e] > 0 && (l == -1 || L.b[i]/L.A[i][e] < L.b[l]/L.A[l][e])){l = i;}
		}
		// if not constraint, return unbounded
		if(l == -1){cout << "unbounded\n"; return false;}
		
		// swap a non-basic variable with non-negative objective function cofficient
		pivot(L, l, e);
	}
	return true;
}


// convert original linear program into equivalent linear program with initial feasible solution
bool initialisePreflow(linearprogram &L)
{
	// check for initial feasible solution
	int minb = L.basic[0];
	for(int l1 = 0; l1 < L.m; l1++)
	{
		int j = L.basic[l1];
		if(L.b[j] < L.b[minb]){minb = j;}
	}
	// if initial solution (all non-basic zeroes) feasible
	if(L.b[minb] >= 0)		// all b's are positive
	{
		// return;
		return true;
	}
	// change to feasible
	else
	{
		// store objective function
		int n = L.n;
		int m = L.m;
		for(int l1 = 0; l1 < L.n+L.m; l1++)
		{
			ct[l1] = L.c[l1];
		}
		
		
		// add new non-basic index n+m;
		for(int l1 = 0; l1 < L.m; l1++)
		{
			int i = L.basic[l1];
			L.A[i][n+m] = -1;
		}

		
		// change objective function
		for(int l1 = 0; l1 < L.n+L.m; l1++)
		{
			L.c[l1] = 0;
		}

		L.c[n+m] = -1;
		L.nonbasic[L.n] = n+m;
		L.n++;

		int l = minb;
		int e = n+m;
		pivot(L, l, e);
		
		// pivot untill initial solution is feasible
		basicloop(L);

		// check for initial solution
		for(int l1 = 0; l1 < L.n; l1++)
		{
			int j = L.nonbasic[l1];
			del[j] = 0;
		}
		for(int l1 = 0; l1 < L.m; l1++)
		{
			int i = L.basic[l1];
			del[i] = L.b[i];
		}
		
		// if not feasible, return
		if(del[n+m] != 0){cout << "infeasible\n";return false;}
		
		// delete varible n+m
		l = -1;
		for(int l1 = 0; l1 < L.m; l1++)
		{
			int i = L.basic[l1];
			if(i == n+m){l = l1;break;}
		}
		if(l != -1)
		{
			int e = -1;
			for(int l1 = 0; l1 < L.n; l1++)
			{
				int j = L.nonbasic[l1];
				if(L.A[l][j] > 0 && (e == -1 || L.b[l]/L.A[l][j] < L.b[l]/L.A[l][e])){e = j;}
			}
			if(e != -1){pivot(L, l, e);}
		}
		for(int l1 = 0; l1 < L.n; l1++)
		{
			if(L.nonbasic[l1] == n+m){l = l1;break;}
		}

		// restore objective function
		for(int l1 = 0; l1 < L.n+L.m; l1++)
		{
			L.c[l1] = 0;
		}
		for(int l1 = 0; l1 < L.n; l1++)
		{
			int j = L.nonbasic[l1];
			L.c[j] = ct[j];
		}
		for(int l1 = 0; l1 < L.m; l1++)
		{
			int i = L.basic[l1];
			for(int l2 = 0; l2 < L.n; l2++)
			{
				int j = L.nonbasic[l2];
				L.c[j] += ct[i]*L.A[i][j];
			}
		}
		swap(L.nonbasic[l], L.nonbasic[L.n-1]);
		L.n--;

		return true;
	}
}

// simplex algorithm for solving linear-programming problems
void simplex()
{
	// change from standard to slack form;
	standardtoslack(L);
	// check for initial feasible solution
	bool feasible = initialisePreflow(L);
	if(feasible)
	{
		// pivot ,untill objective function has all neagtive cofficients
		basicloop(L);
	}
}
