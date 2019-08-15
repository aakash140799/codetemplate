

// dynamically resized array
template<class type> class dynamicarray
{
	public:
	type *arr;
	int size;
	int cap;

	dynamicarray()
	{
		arr = new type[2];
		size = 0;
		cap = 2;
	}
	// push-back function
	void pushb(type v)
	{
		arr[size++] = v;

		if(size == cap)
		{
			increasecap();
		}
	}
	// pop-back function
	void popb()
	{
		size--;
		if(size <= (cap/4))
		{
			decreasecap();
		}
	}
	// increase len of array
	void increasecap()
	{		
		if(size == cap)
		{
			type *t = new type[cap*2];
			for(int i = 0;i < size;i++)
			{
				t[i] = arr[i];
			}
			cap *= 2;

			delete []arr;
			arr = t;
		}
	}
	// decrease len of array
	void decreasecap()
	{
		if(size <= cap/4 && cap >= 4)
		{
			type *t = new type[cap/2];
			for(int i = 0;i < size;i++)
			{
				t[i] = arr[i];
			}
			cap /= 2;

			delete []arr;
			arr = t;
		}
	}
	// change len of array according to need
	void recap(int capt)
	{
		if(size <= capt)
		{
			type *t = new type[capt];
			for(int i = 0;i < size;i++)
			{
				t[i] = arr[i];
			}
			cap = capt;

			delete []arr;
			arr = t;
		}
	}
	// change size;
	void resize(int sizet)
	{
		if(sizet <= cap)
		{
			size = sizet;
		}
	}
};