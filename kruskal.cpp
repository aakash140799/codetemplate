

// define graph//
// define disjoing set//


const int esize = 100; // size of edges in tree
// less function for sorting edges
template<class type> bool wsort(edge e1,edge e2)
{
	return e1.w < e2.w;
}


edge edgelist[esize];
// run kruskal algorithm for min-spanning tree;
template<class type> int kruskal()
{
	// sort edges accoring to increasing weights
	sort(graph.E, graph.E+graph.m, wsort<type>);

	// len of edgelist
	int c = 0;
	// connect vertices in graph, untill whole graph is connected.
	for(int i = 0;i < graph.m;i++)
	{
		// if ith edge's vertices are not in same group, add to tree.
		if(find(graph.E[i].u) != find(graph.E[i].v))
		{
			edgelist[c++] = graph.E[i];
			merge(graph.E[i].u, graph.E[i].v);
		}
	}
	return c;
}
