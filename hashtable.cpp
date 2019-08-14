

// define tnil//
// define tdel//
// define linkedlist//

int division(keytype);
int multiplication(keytype);
const int tablesize = 100;

// hash table using linked list to resolve collsion;
template<class keytype> class hashtable
{
	public:
	linkedlist<keytype> table[tablesize];
	// set to hash-function used;
	int (*h)(keytype);

	// intialise to division function
	hashtable<keytype>()
	{
		h = &division;
	}


	void insert(keytype key)
	{
		int ind = h(key);
		table[ind].push(table[ind].end, key);	// push key at back of list
	}


	vertice<keytype> *search(keytype key)
	{
		int ind = h(key);
		vertice<keytype> *k = 0;

		for(vertice<keytype> *i = table[ind].head.n; i != &table[ind].end; i = i->n)
		{
			if(i->v == key){k = i;break;}
		}
		return k;
	}


	void erase(keytype key)
	{
		vertice<keytype> *k = search(key);
		if(k != 0){table[h(key)].erase(k);}
	}
};


// hash table using open-hashing
template<class keytype> class openhash
{
	public:
	keytype table[tablesize];

	// 1st function for probing
	int (*h1)(keytype);
	// 2nd function for probing
	int (*h2)(keytype);
	// probing function
	int (openhash<keytype>::*prob)(keytype, int);

	

	openhash()
	{
		for(int i = 0;i < tablesize;i++)
		{
			table[i] = tnil;
		}
		h1 = &division;
		h2 = &division;
		prob = &linearprob;
	}
	void insert(keytype key)
	{
		int i = 0;
		while(i < tablesize)
		{
			int ind = (*this.*prob)(key, i);
			if(table[ind] == tnil || table[ind] == tdel){table[ind] = key;break;}
			i++;
		}
	}
	int search(keytype key)
	{
		int i = 0;
		int l = -1;
		while(i < tablesize)
		{
			int ind = (*this.*prob)(key, i);
			if(table[ind] == key){l = ind;break;}
			if(table[ind] == tnil){break;}
			i++;
		}

		return l;
	}
	void erase(keytype key)
	{
		int i = 0;
		while(i < tablesize)
		{
			int ind = (*this.*prob)(key, i);
			if(table[ind] == key){table[ind] = tdel;break;}
			if(table[ind] == tnil){break;}
			i++;
		}
	}


	// list of probing functions
	int linearprob(keytype key,int i)
	{
		return (h1(key)+i)%tablesize;
	}
	int quadraticprob(keytype key,int i)
	{
		int c1 = 214;	// random number
		int c2 = 4412;	// random number
		return (h1(key)+ c1*i + c2*i*i)%tablesize;
	}
	int doubleprob(keytype key,int i)
	{
		return (h1(key)+ i*h2(key))%tablesize;
	}
};


// hash table using double hashing technique;
template<class keytype> class perfecthash
{
	public:
	openhash<keytype> table[tablesize];
	// 1st hashing function for probing
	int (*h1)(keytype);
	// 2nd hashing function for probing
	int (*h2)(keytype);
	// probing function
	int (perfecthash<keytype>::*prob)(keytype, int);


	perfecthash()
	{
		h1 = &division;
		h2 = &division;
		prob = &linearprob;
	}
	void insert(keytype key)
	{
		table[h1(key)].insert(key);
	}
	int search(keytype key)
	{
		int i = -1;
		i = table[h1(key)].search(key);
		return i;
	}
	void erase(keytype key)
	{
		table[h1(key)].erase(key);
	}

	// list of probing functions
	int linearprob(keytype key,int i)
	{
		return (h1(key)+i)%tablesize;
	}
	int quadraticprob(keytype key,int i)
	{
		int c1 = 214;	// random number
		int c2 = 4412;	// random number
		return (h1(key)+ c1*i + c2*i*i)%tablesize;
	}
	int doubleprob(keytype key,int i)
	{
		return (h1(key)+ i*h2(key))%tablesize;
	}
};


// list of hash-functions
int division(keytype key)
{
	return key%tablesize;
}
int multiplication(keytype key)
{
	float A = 0.1411233;
	A *= key;

	A -= (int)A;
	if(A < 0){A = -A;}

	A *= tablesize;
	A = (int)A;

	return A;
}


