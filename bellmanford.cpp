


// define graph//
// define d in vertice, w in edges//


const int posinf = 1000000000;
// run single-point shortest path algoritm- bellman ford
void bellmanford(int src)
{
	// set distance to all vertices to infinite
	for(int i = 1;i <= graph.n;i++)
	{
		graph.V[i].d = posinf;
	}

	// set distance to source equal to zerp
	graph.V[src].d = 0;

	// run iteration from 1 to n;
	for(int i = 1;i <= graph.n;i++)
	{
		// relax each edge in the graph
		for(int j = 0;j < graph.m;j++)
		{
			edge e = graph.E[j];
			if(graph.V[e.v].d > graph.V[e.u].d+e.w)
			{
				graph.V[e.v].d = graph.V[e.u].d+e.w;
			}
		}
	}
}