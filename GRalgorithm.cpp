

// GR algorithm // 
// define preference from u->v with directed graphu //
// define preference from v->u with directed graphv //
// define queue data-structure que, (for code, using queue.cpp);


// current index of edge(u,v) in preference list of u ,graphu
int current[vsize];


// current pairing of u
int pairingu[vsize];


// current pairing of v
int pairingv[vsize];


void GR(int n,	int m)
{

	// set all u,v to non-paired state
	fill(pairingu, pairingu+n+1, 0);
	fill(pairingv, pairingv+m+1, 0);
	
	
	// set all u's current top in preference list
	for(int u = 1; u <= n; u++)
	{
		current[u] = graphu.V[u].p;
		que.push(u);
	}



	while(que.size > 0)
	{
		// current u in lst
		int u = que.front();
		que.pop();


		// check all v in preferece list of u, untill paired
		while(  current[u] < graphu.V[u].r   && pairingu[u] == 0)
		{

			// current v in preference list
			int v = graphu.E[current[u]].v;
	
			// check for preference of u in v's preference list;
			edge e;
			e.u = v; e.v = u;
			int prefs = graphv.ingraph(e);


			// if v do not prefer u at all, then pass
			if(prefs == -1){}

			// else if v is unpaired
			else if(pairingv[v] == 0)
			{
				// pair with u
				pairingu[u] = v;
				pairingv[v] = u;
			}
			else
			{

				// preference number of u in v's preference list;
				e.u = v; e.v = u;
				int indu = graphv.ingraph(e);	// ingraph return index of edge e;


				// preference number of ut-current pair in v's preference list;
				e.u = v; e.v = pairingv[v];
				int indut = graphv.ingraph(e);


				// if u is more prefered over current pairing
				if(graphv.E[indu].pref > graphv.E[indut].pref)
				{
					// re-pair
					pairingu[u] = v;
					int ut = pairingv[v];
					pairingv[v] = u;

					// un-pair last pairing;
					// add to back of list for rechecking
					pairingu[ut] = 0;
					que.push(ut);
				}
			}

			current[u]++;
		}
	}
}
