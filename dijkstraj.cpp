



// define graph//
// define minheap//


const int posinf = 1000000000;
int vset[vsize];
// runs single-point shortest path algorithm: dijkstra, runs with positive weights only
void dijkstra(int src)
{
	// set distance to all vertices equal to infinte
	for(int i = 1;i <= graph.n;i++)
	{
		graph.V[i].d = posinf;
		vset[i] = 0;
	}

	// set distance to src equal to zero;
	graph.V[src].d = 0;
	minheap.push(src);


	while(minheap.size())
	{
		// remove all already set vertices;
		while(vset[minheap.top()] == 1){minheap.pop();}
		
		// find min-distant vertice
		int top = minheap.top();minheap.pop();

		// add vertice to list of vertices set
		vset[top] = 1;
		// relax all vertices neighbour to top;
		for(int i = graph.V[top].p;i < graph.V[top].r;i++)
		{
			Graph::edge e = graph.E[i];
			if(graph.V[e.v].d > graph.V[top].d+e.w)
			{
				graph.V[e.v].d = graph.V[top].d+e.w;
				minheap.push(e.v);
			}
		}
	}
}
