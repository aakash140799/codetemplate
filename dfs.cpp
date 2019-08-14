

// define graph//
// define stk//


const int vsize = 100;
int start[vsize];
int end[vsize];
int pushed[vsize];
// runs search on graph according to dfs, sets start and end values according to time of expansion
void dfs(int src)
{
	// set all vertices' pushed to zero
	for(int i = 1;i <= graph.n;i++){pushed[i] = 0;}

	// start time count to zero
	int c = 0;
	// push src on stack
	stk.push(src);
	pushed[src] = 1;
	
	while(stk.size())
	{
		int top = stk.top();stk.pop();
		// if first-time pushed
		if(pushed[top] == 1)
		{
			// set start time
			start[top] = c++;

			stk.push(top);
			pushed[top] = 2;

			// push all child of top
			for(int i = graph.V[top].p; i < graph.V[top].r; i++)
			{
				if(pushed[graph.E[i].v] == 0)
				{
					stk.push(graph.E[i].v);
					pushed[graph.E[i].v] = 1;
				}
			}
		}
		// if second-time pushed
		else
		{
			// set end-time
			end[top] = c++;
		}
	}
}