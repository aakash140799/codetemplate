



const int arrsize = 100;
template<class type> class vertice
{
	public:
	vertice<type> *n;
	type v;
};

const type nulv;
template<class type> class stack
{
	public:
	vertice<type> head;

	stack()
	{
		head.n = 0;
	}
	void push(type v)
	{
		vertice<type> *t = new vertice<type>;
		t->v = v;

		t->n = head.n;
		head.n = t;
	}
	type top()
	{
		if(head.n != 0)
		{
			return head.n->v;
		}
		else{return nulv;}
	}
	void pop()
	{
		if(head.n != 0)
		{
			vertice<type> *t = head.n;
			head.n = head.n->n;

			delete t;
		}
	}
};


// stack implementation using array
template<class type> class stackarray
{
public:
	type v[arrsize];
	int c;

	stackarray()
	{
		c = 0;
	}
	void push(type vt)
	{
		if(c < arrsize)
		{
			v[c++] = vt;
		}
	}
	type top()
	{
		if(c > 0)
		{
			return v[c-1];
		}
	}
	void pop()
	{
		if(c > 0)
		{
			c--;
		}
	}
};