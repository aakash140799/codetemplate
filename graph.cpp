



const int vsize = 100;
const int esize = 100;
class vertice
{
public:
	int p;
	int r;
};

class edge
{
public:
	int u;
	int v;
	bool operator<(edge arg)
	{
		return u < arg.u || (u == arg.u && v < arg.v);
	}
};


// add edges in any order in E[], then call set();
// after set(), E[ V[i].p -> V[i].r] are edges corresponding to vertice i;
// V[i].p and V[i].r are start and end index of edges in E[], correspoding to vertice i;
class Graph
{
public:
	vertice V[vsize];
	edge E[esize];
	int n, m;

	// call after all edges are added
	void set()
	{
		sort(E, E+m);
		for(int i = 1;i <= n;i++){V[i].p = V[i].r = 0;}

		V[E[0].u].p = 0;
		E[m].u = -1;

		for(int i = 1;i <= m;i++)
		{
			if(E[i-1].u != E[i].u)
			{
				V[E[i-1].u].r = i;
				V[E[i].u].p = i;
			}
		}
	}
	
	// return index of edge e in graph
	int ingraph(edge e)
	{
		int p = V[e.u].p;
		int r = V[e.u].r;
		int i = -1;

		while(r-p > 0)
		{
			int q = (p+r)/2;
			if(E[q].v == e.v){i = q;break;}
			else if(E[q].v < e.v){p = q+1;}
			else if(E[q].v > e.v){r = q;}
		}

		return i;
	}
	// addedge another egde, set() need to be called manually
	void addedge(int u,int v)
	{
		E[m].u = u;E[m].v = v;
		m++;
	}

};
