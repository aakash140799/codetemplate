


// define que//
// define graphbfs//


const int vsize = 100;
int parent[vsize];
int pushed[vsize];

// sets parent of each vertice according to its parent in bfs-run
void bfs(int src)
{
	// set pushed of all vertices to zero;
	for(int i = 1;i <= graph.n;i++){pushed[i]=0;}

	// push src into queue;
	que.push(src);
	parent[src] = 0;
	pushed[src] = 1;


	// run iteration of vertices in queue;
	// new vertices searcher , goes in last of queue;
	while(que.size())
	{
		int front = que.front(); que.pop();
		for(int i = graph.V[front].p;i < graph.V[front].r;i++)
		{
			if(pushed[graph.E[i].v] == 0)
			{
				parent[graph.E[i].v] = front;
				que.push(graph.E[i].v);
				pushed[graph.E[i].v] = 1;
			}
		}
	}
}

// create graphbfs using parent array
void creategraph()
{
	graphbfs.n = graph.n;
	graphbfs.m = 0;
	for(int i = 1;i <= graph.n;i++)
	{
		graphbfs.addedge(parent[i], i);
	}
	graphbfs.set();
}