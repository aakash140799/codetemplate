

// number of employeed bees
const int s = 100;

// number of onlooker bees;
const int m = 20;

// number of parameters in objFunc
const int n = 10;

// min-value for one parameter
const float xmin = -5.16;

// max-value for one parameter
const float xmax = 5.16;

// max counter value for scount bees
const int maxcount = 100;


class ABC
{
	public:
	class candidate
	{
		public:
		float xVals[n];
		float objVal;
		float fitVal;

		bool operator<(const candidate arg)
		{
		    return fitVal > arg.fitVal;
		}
	};
	candidate pos[s];
	int counter[s];
	candidate look[s];
	candidate bestpos;



	//////////// some utility functions //////////////

	// random number generator
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

	// floating-point random number generator for x in [0,1]
	float randr()
	{
		return (float)(rand()%1000)/1000.0;
	}

	// floating-point random number genarator for x in [-1,1]
	float randp()
	{
		return (float)((rand()%2000)-1000)/1000.0;
	}

	// set xVals, objVal , fitVals of population
	void set(candidate *pop)
	{
		for(int i = 0;i < s;i++)
		{
			pop[i].objVal = objFunction(pop[i].xVals);
			pop[i].fitVal = fitFunction(pop[i].objVal);
		}
		sort(pop, pop+s);
	}

	// normalize fitVals according to roulette wheel
	void normalize(candidate *pop)
	{
		for(int i = 1;i < s;i++){pop[i].fitVal += pop[i-1].fitVal;}
		for(int i = 0;i < s;i++){pop[i].fitVal /= pop[s-1].fitVal;}
	}

	// select one particle according to roulette wheel
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
	float fitFunction(float objarg)
	{
		return -objarg;
	}



	// initilise population randomly
	void initialise()
	{
		for(int i = 0;i < s;i++)
		{
			for(int j = 0;j < n;j++)
			{
				pos[i].xVals[j] = randr()*(xmax-xmin) + xmin;
			}
			counter[i] = 0;
		}
		set(pos);
		bestpos = pos[0];
	}

	// employeed bee phase
	void employeed()
	{
		for(int i = 0;i < s;i++)
		{
			// select j randomly
			int j = rand()%s;
			while(j == i){j = rand()%s;}

			// select k randomly
			int k = rand()%n;
			look[i] = pos[i];

			// mutate vector
			look[i].xVals[k] = pos[i].xVals[k] + (randp()*(pos[j].xVals[k]-pos[i].xVals[k]));


			if(look[i].xVals[k] > xmax){look[i].xVals[k] = xmax;}
			else if(look[i].xVals[k] < xmin){look[i].xVals[k] = xmin;}

			look[i].objVal = objFunction(look[i].xVals);
			look[i].fitVal = fitFunction(look[i].objVal);
		}

		for(int i = 0;i < s;i++)
		{
			if(look[i].fitVal > pos[i].fitVal)
			{
				pos[i] = look[i];
				counter[i] = 0;
			}
			else
			{
				counter[i]++;
			}

			if(pos[i].fitVal > bestpos.fitVal)
			{
				bestpos = pos[i];
			}
		}
	}


	// onlooker bee phase
	void onlooker()
	{
		copy(pos, pos+s, look);
		normalize(look);
		for(int i = 0;i < m;i++)
		{
			int c = wheelselect(look);
			int k = rand()%n;
			counter[k]++;
		}
	}


	// scout bee phase
	void scout()
	{
		for(int i = 0;i < s;i++)
		{
			if(counter[i] >= maxcount)
			{
				for(int j = 0;j < n;j++)
				{
					pos[i].xVals[j] = randr()*(xmax-xmin) + xmin;
				}
				counter[i] = 0;
			}
		}

		set(pos);
	}

	// iterate for t generations
	void iterate(int t = 1000)
	{
		initialise();
		for(int i = 0;i < t;i++)
		{
			employeed();
			onlooker();
			scout();
		}

		cout << bestpos.fitVal << "\n";
	}
};

