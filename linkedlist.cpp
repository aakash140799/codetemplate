


const int arrsize = 100;
template<class type> class linkedlist
{
	public:

	// type of vertice in list
	class vertice
	{
	public:
	vertice *n;
	vertice *p;
	type v;
	vertice(){n = p = 0;}
	};


	// head and end sentinels for list;
	vertice head;
	vertice end;


	linkedlist()
	{
		head.n = &end;
		end.p = &head;
	}


	// push at front
	void pushf(type v)
	{
		vertice *t = new vertice;
		t->v = v;

		t->n = head.n;
		t->p = &head;
		head.n->p = t;
		head.n = t;
	}

	// push at back
	void pushb(type v)
	{
		vertice *t = new vertice;
		t->v = v;

		t->n = &end;
		t->p = end.p;
		end.p->n = t;
		end.p = t;
	}

	// pushes v at ith iterator. ith iterated value goes to i+1;
	void push(vertice *i, type v)
	{
		if(i == &head){return;}
		vertice *t = new vertice;
		t->v = v;

		t->n = i;
		t->p = i->p;
		i->p->n = t;
		i->p = t;
	}

	// erase ith iterator
	void erase(vertice *i)
	{
		if(i == &head || i == &end){return;}

		i->n->p = i->p;
		i->p->n = i->n;
		delete i;
	}

	// pop vertice at front
	void popf(){erase(head.n);}
	// pop vertice at back
	void popb(){erase(end.p);}
	// returns value at front
	type front() {return head.n->v;}
	// returns value at back
	type back(){return end.p->v;}
};



// another implementation using array
template<class type> class linkedlistarray
{
public:

	// prev[i] = previous vertice of i
	int p[arrsize];


	// next[i] = next vertice of i
	int n[arrsize];


	// v[i] = value at vertice i
	type v[arrsize];


	// no of vertices in list
	int l;

	linkedlistarray()
	{
		n[0] = 1;
		p[1] = 0;
		l = 2;
	}


	// linkedlist ordering remains same, but values at i1, and i2 are swaped.
	void exchange(int i1,int i2)
	{
		int i1n, i1p, i2n, i2p;
		i1n = n[i1]; i1p = p[i1];
		i2n = n[i2]; i2p = p[i2];
		n[i1p] = i2;
		p[i1n] = i2;
		n[i2p] = i1;
		p[i2n] = i1;
		swap(n[i1], n[i2]);
		swap(p[i1], p[i2]);
		swap(v[i1], v[i2]);
	}


	// push value in front
	void pushf(type vt)
	{
		v[l] = vt;
		p[l] = 0;
		n[l] = n[0];
		p[n[0]] = l;
		n[0] = l;
		l++;
	}
	

	// push value in end;
	void pushb(type vt)
	{
		v[l] = vt;
		n[l] = 1;
		p[l] = p[1];
		n[p[1]] = l;
		p[1] = l;
		l++;
	}
	

	// push value at index i;
	void push(int i,type vt)
	{
		v[l] = vt;
		n[l] = i;
		p[l] = p[i];
		n[p[i]] = l;
		p[i] = l;
		l++;
	}
	

	// erase value at index i
	void erase(int i)
	{
		if(i != 0 && i != 1)
		{
			exchange(i, l-1);
			n[p[l-1]] = n[l-1];
			p[n[l-1]] = p[l-1];
			l--;
		}
	}
	

	// returns value in front
	type front(){return v[n[0]];}
	// returns value in end;
	type back(){return v[p[1]];}
	// pops value at front
	void popf(){erase(n[0]);}
	// pops value at end;
	void popb(){erase(p[1]);}
};
