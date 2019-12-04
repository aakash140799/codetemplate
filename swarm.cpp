

// poppulation size
const int s = 100;

// number of parameters in objFunc
const int n = 10;

// alpha and beta parameters
const float a = 2;
const float b = 2;

// min and max bound for objective function parameters
const float xmax = 5.16;
const float xmin = -5.16;

// weight paramter
const float phi = 0.9;

// max-velocity
const float vmax = 2;

class swarm
{
	public:
	class particle
	{
		public:
		float xVals[n];
		float objVal;
		float fitVal;
	};
	particle pos[s];
	particle vel[s];
	particle lbest[s];
	particle gbest;


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

	// random floating-point value generator
	float randr()
	{
		return (float)(rand()%1000)/1000.0;
	}

	// set population objValue, fitness value
	void set(particle *pop)
	{
		for(int i = 0;i < s;i++)
		{
			pop[i].objVal = objfunction(pop[i].xVals);
			pop[i].fitVal = fitfunction(pop[i].objVal);
		}
	}

	////////////  Utility functions above ////////////



	// code for objective function goes here
	float objfunction(float *xVals)
	{
		float x = 0;
		for(int i = 0;i < n;i++)
		{
			x += (xVals[i]*xVals[i]);
		}

		return x;
	}


	// code for fitness function goes here
	float fitfunction(float objArg)
	{
		return -objArg;
	}


	// set initial positions randomly
	void initialise()
	{
		for(int i = 0;i < s;i++)
		{
			for(int j = 0;j < n;j++)
			{
				pos[i].xVals[j] = randr()*(xmax-xmin) + xmin;
			}
		}
		set(pos);

		gbest = pos[0];
		for(int i = 0;i < s;i++)
		{
			lbest[i] = pos[i];
			if(lbest[i].fitVal > gbest.fitVal)
			{
				gbest = lbest[i];
			}
		}
	}

	// update pos by velocity vector
	void update()
	{

		// calculate velocity vectors
		for(int i = 0;i < s;i++)
		{
			for(int j = 0;j < n;j++)
			{
				// update equation
				vel[i].xVals[j] = (phi*vel[i].xVals[j]) + (randr()*a*(lbest[i].xVals[j]-pos[i].xVals[j])) + (randr()*b*(gbest.xVals[j]-pos[i].xVals[j]));


				if(vel[i].xVals[j] > vmax){vel[i].xVals[j] = vmax;}
				else if(vel[i].xVals[j] < -vmax){vel[i].xVals[j] = -vmax;}
			}
		}

		// update by velocity vectors
		for(int i = 0;i < s;i++)
		{
			for(int j = 0;j < n;j++)
			{
				pos[i].xVals[j] += vel[i].xVals[j];

				if(pos[i].xVals[j] > xmax){pos[i].xVals[j] = xmax;}
				else if(pos[i].xVals[j] < xmin){pos[i].xVals[j] = xmin;}
			}
		}
		set(pos);

		// update lbest and gbest
		for(int i = 0;i < s;i++)
		{
			if(pos[i].fitVal > lbest[i].fitVal)
			{
				lbest[i] = pos[i];
			}
			if(pos[i].fitVal > gbest.fitVal)
			{
				gbest = pos[i];
			}
		}

	}


	// iterate for t generations
	void iterate(int t = 1000)
	{
		initialise();
		for(int i = 0;i < t;i++)
		{
			update();
		}
		cout << gbest.fitVal << "\n";
	}
};

