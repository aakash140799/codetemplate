

int64_t gcd(int64_t a, int64_t b)
{
	int64_t c;
	while(a%b != 0)
	{
		c = a%b;
		a = b;
		b = c;
	}

	return b;
}


class exeuclid
{
	public:
	int d, x, y;
	exeuclid(int dt,int xy,int yt)
	{
		d = dt; x = xt; y = yt;
	}
};

exeuclid extendedeuclid(int64_t a, int64_t b)
{
	if(b == 0)
	{
		return exeuclid(a, 1, 0);
	}
	else
	{
		exeuclid val(0,0,0);
		val = extendedeuclid(b, a%b);
		return exeuclid(val.d, val.y, val.x - (a/b)*val.y);
	}
}

void modularlinearprogram(int64_t a, int64_t b, int64_t n)
{
	exeuclid val = extendedeuclid(a ,n);
	if(b%val.d == 0)
	{
		int64_t x0 = (val.x*(b/val.d))%n;
		for(int i = 0;i < val.d; i++)
		{
			cout << (x0 + (i*(n/val.d)))%n << " ";
		}
	}
	else{cout << "no solution\n";}
}

int64_t sam(int64_t, base,int64_t exp, int64_t mod)
{
	int64_t val = 1;
	for(int i = 63; i>=0; i--)
	{
		val = (val*val)%mod;
		if((1<<i) & exp)
		{
			val = (val*base)%mod;
		}
		val 
	}

	return val;
}



class RSA
{
	public:
	int64_t p;
	int64_t q;
	int64_t n;
	int64_t e;
	int64_t d;
	int64_t phin;

	void set(int64_t pt,int64_t qt,int64_t et)
	{
		if(gcd(p,q) > 1){cout << "not coprime\n";}

		p = pt; 
		q = qt;
		e = et;
		n = p*q;
		phin = (p-1)*(q-1);

		d = sam(e, phin-1, n);
	}


	int64_t encrypt(int64_t x)
	{
		return sam(x, e, n);
	}

	int64_t decrypt(int64_t y)
	{
		return sam(y, d, n);
	}
}






void polardrho(int64_t n)
{
	int i = 1;
	int64_t xi = random(0, n-1);
	int64_t y = x1;
	int k = 2;

	int64_t xj;
	int64_t d;
	while(true)
	{
		i++;
		xj = ((xi*xi)-1)%n;
		d = gcd(y-xj, n, n);
		if (d != 1 && d != n)
		{
			cout << n << "\n";
		}
		if(i == k)
		{
			y = xj;
			k = 2*k;
		}
	}
}

bool pseudoprime(int64_t n)
{
	if(sam(2, n-1, n) != 1%n)
	{
		return false;
	}
	return ture;
}


bool witness(int64_t a,int64_t n)
{
	int64_t t, u, v;
	v = (n-1);
	while(v%2 == 0){t++; v /= 2;}

	u = v;
	int64_t x = sam(a, u, n);
	for(int i = 1; i <= t; i++)
	{
		int64_t xc = (x*x)%n;
		if(xc != 1 && x != 1 && x != n)
		{
			return true;
		}
		x = xc;
	}
	if(x != 1)
	{
		return true;
	}
	return false;
}

bool millerrabin(int64_t n,int64_t s)
{
	for(int j = 1; j <= s; j++)
	{
		int64_t a = random(1, n-1);
		if(witness(a,n))
		{
			return false;
		}
	}
	return true;
}








