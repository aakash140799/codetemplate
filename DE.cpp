
// poppulation size
const int s = 100;

// number of parameters in objFunc
const int n = 10;

// min-value for one parameter
const float xmin = -5.16;

// max-value for one parameter
const float xmax = 5.16;

// cross-over probabilty
const float cr = 0.9;

// differential weight
const float f = 0.9;

class DE
{
	public:
	class particle
	{
		public:
		float xVals[n];
		float objVal;
		float fitVal;
	};

	particle population[s];
	particle vectorupd[s];
	particle mostfit;


	//////////// Some Utility Functions ////////////

	// a random number generator
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

	// random floating-point generator
	float randr()
	{
		return (rand()%1000)/1000.0;
	}

	// set objVal,fitVal and sort by fitVal
	void set(particle *pop)
	{
		for(int i = 0;i < s;i++)
		{
			pop[i].objVal = objFunction(pop[i].xVals);
			pop[i].fitVal = fitFunction(pop[i].objVal);
		}
	}

	//////////// Utility Functions Above ////////////


	// code for objective function goes here
	float objFunction(float *xVals)
	{
		float x = 0;
		for(int i = 0;i < n;i++)
		{
			x += (xVals[i]*xVals[i]);
		}

		return x;
	}

	// code for fitness function goes here
	float fitFunction(float objarg)
	{
		return -objarg;
	}

	// initilise population randomly
	particle initialise(particle *pop)
	{
		for(int i = 0;i < s;i++)
		{
			for(int j = 0;j < n;j++)
			{
				pop[i].xVals[j] = randr()*(xmax-xmin) + xmin;
			}
		}
		set(pop);

		// find mostfit
		particle mostfitpop = pop[0];
		for(int i = 0;i < s;i++)
		{
			if(pop[i].fitVal > mostfitpop.fitVal){mostfitpop = pop[i];}
		}
		return mostfitpop;
	}

	// cross-over operator
	void crossover()
	{
		for(int i = 0;i < s;i++)
		{
			// choose parameter a, b and c
			int a = rand()%s;
			int b = rand()%s;
			while(b == a){b = rand()%s;}

			int c = rand()%s;
			while(c == a || c == b){c = rand()%s;}


			// create new vector for i
			for(int j = 0;j < n;j++)
			{
				if(randr() <= cr)
				{
					vectorupd[i].xVals[j] = population[i].xVals[a] + f*(population[i].xVals[b]-population[i].xVals[c]);
				}
				else
				{
					vectorupd[i].xVals[j] = population[i].xVals[j];
				}
			}
		}
		set(vectorupd);
	}

	// selection operator
	void selection()
	{
		for(int i = 0;i < s;i++)
		{
			if(vectorupd[i].fitVal > population[i].fitVal)
			{
				population[i] = vectorupd[i];
			}
			if(population[i].fitVal > mostfit.fitVal)
			{
				mostfit = population[i];
			}
		}
	}

	// iterate for t generations
	void iterate(int t = 1000)
	{
		mostfit = initialise(population);
		for(int i = 0;i < t;i++)
		{
			crossover();
			selection();
		}
		cout << mostfit.fitVal << "\n";
	}
};

