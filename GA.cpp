
// poppulation size
const int s = 100;

// number of parameters in objFunc
const int n = 10;

// number of genes used for one parameter
const int m = 10;

// min-value for one parameter
const float xmin = -5.16;

// max-value for one parameter
const float xmax = 5.16;

// max length of cross-over.
const int mlen = 30;


// constants used in objFunc
const float An = 0;
const float A = 10;


// probability of cross-over, mutation
const float pc = 0.95;
const float pm = 0.05;



class GA
{
	public:

	class candidate
	{
		public:
		bool genes[n*m];
		float xVals[n];
		float objVal;
		float fitVal;


		// sort in descending order of fitness.
		bool operator<(candidate &arg)
		{
			return fitVal > arg.fitVal;
		}
	};

	candidate population[s];
	candidate children[s];
	candidate tpop1[s];
	candidate tpop2[s];
	candidate mostfit;


	//////////// some utility functions //////////////


	// a random number generator;
	const int64_t bigp = 99999989;
	int64_t i1 = 41;
	int64_t i2 = 37;
	int64_t i3 = 43;
	int64_t rand()
	{
		int64_t r = (i1*i2 + i3)%bigp;
		i1 = (i2*r +i3)%bigp;
		i2 = (i3*i1 +i2)%bigp;
		i3 = (i2*i3 + r)%bigp;

		return r;
	}

	// random floating-point between 0 and 1 ,with 3 digits precision
	float randr()
	{
		return (float)(rand()%1000)/1000.0;
	}


	// convert binary string to float.
	float binToFloat(bool *bitArg)
	{
		int x = bitArg[0];
		int v = bitArg[0];
		for(int i = 1;i < m;i++)
		{
			x ^= bitArg[i];
			v |= (x<<i);
		}


		float bucket = (xmax-xmin)/(1<<m);
		float xv = (bucket*v)+xmin;

		return xv;
	}



	// set population xVals, objVal, fitVal, and sort
	void set(candidate *pop)
	{
		for(int i = 0;i < s;i++)
		{
			for(int j = 0;j < n;j++)
			{
				pop[i].xVals[j] = binToFloat(pop[i].genes+(j*m));
			}
			pop[i].objVal = objFunction(pop[i].xVals);
			pop[i].fitVal = fitFunction(pop[i].objVal);
		}
	}

	// normalize pop according to roulette wheel.
	void normalize(candidate *pop)
	{
		for(int i = 1;i < s;i++){pop[i].fitVal += pop[i-1].fitVal;}
		for(int i = 0;i < s;i++){pop[i].fitVal /= pop[s-1].fitVal;}
	}


	// select one cross-point
	int crosspointone()
	{
		return (rand())%(n*m);
	}
	// select second cross-point in range mlen
	int crosspointtwo(int k)
	{
		return k + (rand()%mlen);
	}

	// select one pop randomly according to roulette wheel.
	int wheelselect(candidate *pop)
	{
		float pr = randr();

		int p = 0;
		int r = s;
		if(pr <= pop[p].fitVal){return p;}
		else if(pop[r-1].fitVal < pr){return r-1;}
		else
		{
			while(r-p > 1)
			{
				int q = (p+r)/2;
				if(pr <= pop[q].fitVal){r = q;}
				else{p = q;}
			}

			return r;
		}
	}
	////////////  Utility functions above ////////////




	// code for objFunc goes here
	float objFunction(float *xVals)
	{
		float x = 0;
		for(int i = 0;i < n;i++)
		{
			x += (xVals[i]*xVals[i]);
		}

		return x;
	}


	// code for fitness-Fucntion goes here
	float fitFunction(float objArg)
	{
		return -objArg;
	}



	// randomly set initial population
	void initialise()
	{
		for(int i = 0;i < s;i++)
		{
			for(int j = 0;j < n*m;j++)
			{
				population[i].genes[j] = rand()&1;
			}
		}

		set(population);
		sort(population, population+s);
		mostfit = population[0];
	}


	// cross-over arg1, by arg2 with cross-points k1,k2,(k1 <= k2)
	candidate cross(candidate arg1, candidate arg2,int k1,int k2)
	{
		for(int i = max(0,k1);i < min(n*m,k2);i++)
		{
			arg1.genes[i] = arg2.genes[i];
		}

		return arg1;
	}



	// cross-over operator using tournament selection
	void crossover()
	{
		for(int i = 0;i < s;i += 2)
		{
			if(randr() <= pc)
			{
				int k1 = crosspointone();
				int k2 = crosspointtwo(k1);
				children[i] = cross(population[i], population[i+1], k1, k2);
				children[i+1] = cross(population[i+1], population[i], k1, k2);
			}
			else
			{
				children[i] =  population[i];
				children[i+1] = population[i+1];
			}
		}
		set(children);
	}


	// cross-over using Roulette wheel selection
	void crosswheel()
	{
		copy(population, population+s, tpop1);
		normalize(tpop1);


		int c = 0;
		while(c < s)
		{
			int c1 = wheelselect(tpop1);
			int c2 = wheelselect(tpop1);

			if(randr() <= pc)
			{
				int k1 = crosspointone();
				int k2 = crosspointtwo(k1);
				children[c++] = cross(population[c1], population[c2], k1, k2);
				children[c++] = cross(population[c2], population[c1], k1, k2);
			}
		}
		set(children);
	}


	// mutation operator
	void mutation()
	{
		for(int i = 0;i < s;i++)
		{
			if(randr() <= pm)
			{
				int k1 = crosspointone();
				int k2 = crosspointtwo(k1);
				for(int j = max(0,k1);j < min(n*m,k2);j++)
				{
					children[i].genes[j] ^= 1;
				}
			}
		}
		set(children);
	}


	// selection operator
	void selection(bool elitism = true)
	{
		for(int i = 0;i < s;i++)
		{
			population[i] = children[i];
		}
		sort(population, population+s);
		if(population[0].fitVal > mostfit.fitVal)
		{
			mostfit = population[0];
		}
		if(elitism){population[0] = mostfit;}
	}

	// selection by only-best are selected
	void selectionbest()
	{
		for(int i = 0;i < s;i++)
		{
			if(population[i].fitVal < children[i].fitVal)
			{
				population[i].fitVal = children[i].fitVal;
			}
		}
		sort(population, population+s);
		if(population[0].fitVal > mostfit.fitVal)
		{
			mostfit = population[0];
		}
	}

	// run iterations for t generations
	void iterate(int t = 1000)
	{
		initialise();
		for(int i = 0;i < t;i++)
		{
			crossover();
			mutation();
			selection();
		}

		cout << mostfit.fitVal << "\n";
	}
};
