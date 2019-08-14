

// define graph//
// define minheap//


edge edgelist[esize];
int epushed[esize];
int vset[vsize];
// prims algorithm for min. spanning tree
int prims()
{
	// initialise all vertices and edges to not-set
	for(int i = 1;i <= graph.n;i++)
	{
		vset[i] = 0;
	}
	for(int i = 0;i < graph.m;i++)
	{
		epushed[i] = 0;
	}

	// let 1 is src, set 1
	vset[1] = 1;
	// push all edges of 1;
	for(int i = graph.V[1].p; i < graph.V[1].r; i++)
	{
		minheap.push(graph.E[i]);
		epushed[i] = 1;
	}

	// count of vertices set
	int vn = 1;
	// count of edges in edgelist, edges in spanning tree
	int c = 0;
	while(vn < graph.n)
	{
		// find minweight edge
		edge top = minheap.top(); minheap.pop();
		int v;

		// if both ends belong to differnt group, then merge
		if(vset[top.u] == 0 && vset[top.v] == 1)
		{
			vset[top.u] = 1;
			v = top.u;	vn++;
		}
		else if(vset[top.u] == 1 && vset[top.v] == 0)
		{
			vset[top.v] = 1;
			v = top.v;	vn++;
		}
		// else  ignore
		else{continue;}

		// if safe edge
		edgelist[c++] = top;
		// push edges of newly set vertices
		for(int i = graph.V[v].p; i < graph.V[v].r; i++)
		{
			if(epushed[i] == 0)
			{
				minheap.push(graph.E[i]);
				epushed[i] = 1;
			}
		}
	}

	return c;
}