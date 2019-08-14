

const int limiter = 512;
const type neginf = -1000000000;
template<class type>class prv
{
	public:
	int p;
	int r;
	type v;

	void set(int pt,int rt,type vt)
	{
		p = pt;
		r = rt;
		v = vt;
	}
};

template<class type> prv<type> crossingsum(type *arr,int p,int r)
{
	int q = (p+r)/2;

	type lsum = neginf;
	int li = q+1;

	// left-side max sum
	type tsum = 0;
	for(int i = q-1;i >= p;i--)
	{
		tsum += arr[i];
		if(tsum > lsum)
		{
			lsum = tsum;
			li = i;
		}
	}

	type rsum = neginf;
	int ri = q-1;

	// right-side max sum
	tsum = 0;
	for(int i = q;i < r;i++)
	{
		tsum += arr[i];
		if(tsum > rsum)
		{
			rsum = tsum;
			ri = i;
		}
	}

	prv<type> sum;
	sum.set(li, ri+1, lsum+rsum);
	return sum;
}

template<class type> prv<type> subarraysum(type *arr,int p,int r)
{
	if(r-p > limiter)
	{
		int q = (p+r)/2;
		prv<type> sum1 = subarraysum(arr, p, q);	// left-side sum
		prv<type> sum2 = subarraysum(arr, q, r);	// right-side sum
		prv<type> sum3 = crossingsum(arr, p, q);	// crossing sum

		if(sum1.v > sum2.v && sum1.v > sum3.v){return sum1;}
		else if(sum2.v > sum1.v && sum2.v > sum3.v){return sum2;}
		else{return sum3;}
	}
	else
	{
		prv<type> sum;
		sum.p = p; sum.r = r; sum.v = neginf;

		for(int i = p;i < r;i++)			// sum by iteration
		{
			type tsum = 0;
			for(int j = i;j < r;j++)
			{
				tsum += arr[j];
				if(tsum > sum.v)
				{
					sum.set(i, j+1, tsum);
				}
			}
		}

		return sum;
	}
}


// another implementation
template<class type> class lmr
{
	public:
	type l;
	type m;
	type r;
	void set(type lt,type mt,type rt)
	{
		l = lt;
		m = mt;
		r = rt;
	}
};

template<class type> lmr<type> Subarraysum(type *arr,int p,int r)
{
	if(r-p > limiter)
	{
		int q = (p+r)/2;

		lmr<type> sum1 = Subarraysum(arr, p, q);
		lmr<type> sum2 = Subarraysum(arr, q, r);
		lmr<type> sum3; sum3.set(sum1.l, sum1.m+sum1.r+sum2.l+sum2.m, sum2.r);

		if(sum1.m > sum2.m && sum1.m > sum3.m){return sum1;}
		else if(sum2.m > sum1.m && sum2.m > sum3.m){return sum2;}
		else{return sum3;}
	}
	else
	{
		lmr<type> sum;
		sum.l = neginf; sum.m = neginf; sum.r = neginf;

		type lsum = 0, rsum = 0;
		for(int i = p;i < r;i++){rsum += arr[i];}

		for(int i = p;i < r;i++)
		{
			type tlsum = lsum;
			type trsum = rsum;
			type tmsum = 0;
			for(int j = i;j < r;j++)
			{
				tmsum += arr[j];
				trsum -= arr[j];
				if(tmsum > sum.m)
				{
					sum.l = tlsum; sum.m = tmsum; sum.r = trsum;
				}
			}

			lsum += arr[i];
			rsum -= arr[i];
		}

		return sum;
	}
}