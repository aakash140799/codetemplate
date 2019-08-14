


int parent[100];
int size[100];
// returns top-most parent of a;
// set all vertices'parent on path to top-most parent;
int find(int a)
{
	// find top-most parent
	int t = a;
	while(parent[t]>0){t = parent[t];}

	// set parent of all vertices on path, to top-most parent
	int t2;
	while(parent[a]>0)
	{
		t2 = parent[a];
		parent[a] = t;
		a = t2;
	}

	// return top-most parent;
	return a;
}

// find top-most parent, and set merge smaller set into larger set
void merge(int a,int b)
{
	a = find(a);
	b = find(b);
	if(a != b)
	{
		if(size[a]>=size[b])
		{
			parent[b] = a;
			size[a] += size[b];
		}else
		{
			parent[a] = b;
			size[b] += size[a];
		}
	}
}