


// insert value in an array;
// insert indexes of values in heap as keys;
// assign less function for comparing values of keys.
const int hsize = 100;
class heap
{
	public:
	int keys[hsize];				// keys[i] = key at i;
	int index[hsize];				// index[key] = index of key in keys;
	bool (*less)(int key1,int key2);
	int n;

	
	heap(){n = 0;}
	// exchange values at index i1, i2 maintaining index
	void exchange(int i1,int i2)
	{
		swap(index[keys[i1]],index[keys[i2]]);
		swap(keys[i1],keys[i2]);
	}

	// push-up value at index i
	void heapup(int i)
	{
		int p = (i-1)/2;
		int l = (p<<1) +1;
		int r = (p<<1) +2;

		while(true)
		{
			int top = p;
			if(l < n && less(keys[l],keys[top])){top = l;}
			if(r < n && less(keys[r],keys[top])){top = r;}

			if(top != p)
			{
				exchange(top, p);
				p = (p-1)/2;
				l = (p<<1) +1;
				r = (p<<1) +2;
			}else{break;}
		}
	}

	// push-down value at index i
	void heapdown(int i)
	{
		int p = i;
		int l = (p<<1) +1;
		int r = (p<<1) +2;

		while(true)
		{
			int top = p;
			if(l < n && less(keys[l],keys[top])){top = l;}
			if(r < n && less(keys[r],keys[top])){top = r;}

			if(top != p)
			{
				exchange(top, p);
				p = top;
				l = (p<<1) +1;
				r = (p<<1) +2;
			}else{break;}
		}
	}

	// add a key, key must be in [1-n]
	void add(int key)
	{
		keys[n] = key;
		index[key] = n;
		n++;
		heapup(n-1);
	}

	// return key at top
	int top()
	{
		return keys[0];
	}

	// remove key at top
	int pop()
	{
		exchange(0,n-1);
		n--;
		heapdown(0);
	}

	// set heap when value of key is increased
	void increase(int key){heapdown(index[key]);}
	// set heap when value of key is decreased
	void decrease(int key){heapup(index[key]);}

};
