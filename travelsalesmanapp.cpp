


// define stack//
// define directed graph//



int dfsrun[100];
int indexed[100];

// set dfsrun according to vertices reached in order of dfs algorithm
int dfs(int s)
{
	stack<int> stk;
	stk.push(s);

	for(int i = 1;i <= graph.n;i++)
	{
		indexed[i] = graph.V[i].p;
	}

	
	int c = 0;
	while(stk.size())
	{
		int top = stk.top();
		dfsrun[c++] = top;

		if(indexed[top] != graph.V[top].r)
		{
			uv e = graph.E[indexed[top]];
			if(indexed[e.v]	== graph.V[e.v].p){stk.push(e.v);}
			indexed[top]++;
		}
		else{stk.pop();}
	}

	return c;
}


// travel salesman approximation algorithm
int travelapp()
{
	// set dfsrun array according to vertices reacher in order of dfs algorithm
	int c = dfs(1);

	int l = 0;
	for(int i = 0;i < graph.n;i++){indexed[i] = 0;}



	// iterate through dfsrun, and remove unnecessary visits
	for(int i = 1;i < c;i++)
	{
		// currently visited vertice
		int current = dfsrun[l];
		// next vertice to visit
		int check = dfsrun[i];


		indexed[current] = 1;
		// while visit to next vertice is unnecessary
		while(i < c-1 && indexed[check] == 1)
		{
			edge e; e.u = current; e.v = dfsrun[i+1];
			// remove next vertice
			if(e.u == e.v || graph.ingraph(e) != -1)
			{
				dfsrun[l+1] = dfsrun[i+1];
				check = dfsrun[i+1];
				i++;
			}else{break;}
		}
		l++;
	}
	// return length of approximate path
	return l+1;
}