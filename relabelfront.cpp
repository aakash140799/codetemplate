



// define graph//
// define linkedlist//
Graph graph;
Graph graphres;
int height[100];
int current[100];
linkedlist<int> l;

const int posinf = 100000000;
// vertice relabel operation
void relabel(int v)
{
	// set height to positive infite
	int mhgt = posinf;
	
	// find minimum height of neighbour vertices with positive edge capacity
	for(int i = graphres.V[v].p;i < graphres.V[v].r;i++)
	{
		Graph:edge e = graphres.E[i];
		if(e.c > 0 && mhgt > height[e.v]){mhgt = height[e.v];}
	}
	// relabel vertice to height greater than minimum height
	height[v] = mhgt+1;
}

// push flow operation on edge e
void pushflow(Graph::edge e)
{
	// index of edge e in flow graph, -1 if not present
	int ig = graph.ingraph(e);
	
	// index of edge e in residual graph, -1 if not present
	int igs = graphres.ingraph(e);
	
	// reverse the edge
	swap(e.u,e.v);
	
	// index of reverse edge in flow graph, or -1
	int igr = graph.ingraph(e);
	
	// index of reverse edge in residual graph, or -1
	int igsr = graphres.ingraph(e);
	
	// reverse the edge back to original
	swap(e.u,e.v);

	// minimum flow push-able
	type f = min(graphres.V[e.u].e, e.c);
	if(ig != -1)
	{
		graph.E[ig].f += f;
	}else
	{
		graph.E[igr].f -= f;
	}

	// change edge capacities in residual graph
	graphres.E[igs].c -= f;
	graphres.E[igsr].c += f;
	
	// push excess flow in residual graph
	graphres.V[e.u].e -= f;
	graphres.V[e.v].e += f;
}

// discharge operation on vertice v
void discharge(int v)
{
	// untill excess flow on v is not zero
	while(graphres.V[v].e > 0)
	{
		// index of current neighbour vertice in list of neighbour vertices
		int i = current[v];
		Graph::edge e = graphres.E[i];
		
		// at end of list
		if(i == graphres.V[v].r)
		{
			relabel(v);
			current[v] = graphres.V[v].p;
		}
		// a push-able edge
		else if(e.c > 0 && height[e.u]==height[e.v]+1)
		{
			pushflow(e);
		}else{current[v]++;} // pass
	}
}

// initailise pre-flow operation
void initialise(int src)
{
	// set inital excess flow and height to zero
	for(int i = 1;i <= graph.n;i++)
	{
		graph.V[i].e = graphres.V[i].e = 0;
		current[i] = graphres.V[i].p;
		height[i] = 0;
	}
	
	// set initial flow to zero
	for(int i = 0;i < graph.m;i++){graph.E[i].f = 0;}
	for(int i = 0;i < graphres.m;i++){graphres.E[i].f = 0;}
	
	// push flow from src to all neighbour vertices
	for(int i = graphres.V[src].p;i < graphres.V[src].r;i++)
	{
		Graph::edge e = graphres.E[i];
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
	// set height of src = number of vertices
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
	linkedlist<int>::vertice *i = l.head.n;
	while(i != &l.end)
	{
		int u = i->v;
		int oldheight = height[u];
		discharge(u);
		
		// if relabel performed
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

