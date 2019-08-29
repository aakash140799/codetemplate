



const int arrsize = 100;
const type nulv;
template<class type> class queue
{
	public:

	class vertice
	{
	public:
	vertice *n;
	type v;
	};


	vertice head;
	vertice *last;

	queue()
	{
		head.n = 0;
		last = &head;
	}
	void push(type v)
	{
		vertice *t = new vertice;
		t->v = v;

		t->n = 0;
		last->n = t;
		last = t;
	}
	type front()
	{
		if(head.n != 0)
		{
			return head.n->v;
		}else{return nulv;}
	}
	void pop()
	{
		if(head.n != 0)
		{
			vertice *t = head.n;
			head.n = head.n->n;

			if(last == t){last = &head;}
			delete t;
		}
	}
};


// queue implementation using array
template<class type> class queuearray
{
	public:
	type v[arrsize];
	int s, e;

	queuearray()
	{
		s = e = 0;
	}
	void push(type vt)
	{
		if(e-s < arrsize)
		{
			v[e%arrsize] = vt;
			e++;
		}
	}
	type front()
	{
		if(s != e)
		{
			return v[s%arrsize];
		}
	}
	void pop()
	{
		if(s != e)
		{
			s++;
		}
	}
};
