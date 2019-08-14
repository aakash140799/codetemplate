
//define undirected graph//

int set[esize];
int cover[2*vsize];
// vertec cover approximation algorithm
void vertexcoverapp()
{
	int c = 0;
	// iterate over all edges
	for(int i = 0;i < graph.m;i++)
	{
		// add one vertice
		cover[c] = graph.E[i].u;

		// remove all edges connected to vertice
		for(int j = graph.V[cover[c]].p;j < graph.V[cover[c]].r;j++)
		{
			set[j] = 1;

			edge e = graph.E[j];
			swap(e.u,e.v);
			int igr = graph.ingraph(e);

			if(igr != -1){set[igr] = 1;}
		}

		// skip untill one non-removed edge found;
		i = graph.V[cover[c]].r;
		while(i < graph.m && set[i] == 1){i++;}
		i--;
		c++;
	}
}
