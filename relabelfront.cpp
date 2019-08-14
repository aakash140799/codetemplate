



// define graph//
// define linkedlist//
Graph graph;
Graph graphres;
int height[100];
int current[100];
linkedlist l;

void relabel(int v)
{
	int mhgt = 1000000000;
	for(int i = graphres.V[v].p;i < graphres.V[v].r;i++)
	{
		edge e = graphres.E[i];
		if(e.c > 0 && mhgt > height[e.v]){mhgt = height[e.v];}
	}

	height[v] = mhgt+1;
}

void pushflow(edge e)
{
	int ig = graph.ingraph(e);
	int igs = graphres.ingraph(e);
	swap(e.u,e.v);
	int igr = graph.ingraph(e);
	int igsr = graphres.ingraph(e);
	swap(e.u,e.v);

	type f = min(graphres.V[e.u].e, e.c);
	if(ig != -1)
	{
		graph.E[ig].f += f;
	}else
	{
		graph.E[igr].f -= f;
	}

	graphres.E[igs].c -= f;
	graphres.E[igsr].c += f;

	graphres.V[e.u].e -= f;
	graphres.V[e.v].e += f;
}

void discharge(int v)
{
	while(graphres.V[v].e > 0)
	{
		int i = current[v];
		edge e = graphres.E[i];
		if(i == graphres.V[v].r)
		{
			relabel(v);
			current[v] = graphres.V[v].p;
		}
		else if(e.c > 0 && height[e.u]==height[e.v]+1)
		{
			pushflow(e);
		}else{current[v]++;}
	}
}

void initialise(int s)
{
	for(int i = 1;i <= graph.n;i++)
	{
		graph.V[i].e = graphres.V[i].e = 0;
		current[i] = graphres.V[i].p;
		height[i] = 0;
	}
	for(int i = 0;i < graph.m;i++){graph.E[i].f = 0;}
	for(int i = 0;i < graphres.m;i++){graphres.E[i].f = 0;}
	for(int i = graphres.V[s].p;i < graphres.V[s].r;i++)
	{
		edge e = graphres.E[i];
		if(e.c > 0)
		{
			int f = graphres.E[i].c;
			
			int ig = graph.ingraph(e);
			swap(e.u,e.v);
			int igsr = graphres.ingraph(e);
			swap(e.u,e.v);

			graph.E[ig].f += f;
			graphres.E[i].c = 0;
			graphres.E[igsr].c = f;

			graphres.V[e.u].e -= f;
			graphres.V[e.v].e += f;
		}
	}
	height[s] = graph.n;
}

// relabel to front algorithm for max-flow networks
void relabelfront(int s,int t)
{
	// initialise preflow
	initialise(s);
	// push all vertices in linkedlist
	for(int i = 1;i <= graph.n;i++)
	{
		if(i == s || i == t){continue;}
		l.pushb(i);
	}
	// set pointer to head;
	vertice<int64_t> *i = l.head.n;
	while(i != &l.end)
	{
		int u = i->v;
		int oldheight = height[u];
		discharge(u);
		// relabel performed
		if(oldheight < height[u])
		{
			// move to front
			l.erase(i);
			l.pushf(u);
			i = l.head.n;
		}
		i = i->n;
	}
}

