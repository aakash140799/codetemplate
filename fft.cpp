// fft algocomplexnumthm

// class of complex numbers;
class complexnum
{
public:
	double real;
	double imag;
	// multiply this by arg
	void mul(complexnum arg)
	{
		complexnum t;
		t.real = real*arg.real - imag*arg.imag;
		t.imag = real*arg.imag + imag*arg.real;
		*this = t;
	}
	// add arg to this
	void add(complexnum arg)
	{
		real += arg.real;
		imag += arg.imag;
	}
	// overload + operator
	complexnum operator+(complexnum arg1,complexnum arg2)
	{
		arg1.real += arg2.real;
		arg1.imag += arg2.imag;
		return arg1;
	}
	// overload - operator
	complexnum operator-(complexnum arg1,complexnum arg2)
	{
		arg1.real -= arg2.real;
		arg1.imag -= arg2.imag;
		return arg1;
	}
	// setter for class
	void set(double r,double i)
	{
		real = r;
		imag = i;
	}
};

// polynomail a, and b
complexnum a[100], b[100];
// value of mathematical pi
double pi = 22.0/7;

// perform discrete fourier transform on a,return a[] with ai = summation(ai* W(i,n)), where W(i,n) is nth root of unity raise to power i;
void dft(complexnum *a,int sign,int n)
{
	// arrange a[] according to base case arrangement of recursion
	for(int i = 1;i < n/2;i += 2)
	{
		swap(a[i],a[n/2+i-1]);
	}


	// find log of n;
	int lgn = 1;
	while((1<<lgn) < n){lgn++;}


	// loop for sth height from below of binary tree of recursion
	for(int s = 1;s <= lgn;s++)
	{
		int m = (1<<s);						// length of array at sth height
		int md2 = m/2;						// length divided by two;
		complexnum wm; wm.set(cos(sign*pi/md2),sin(sign*pi/md2));	// 



		// iterate over n/m internal vertices in sth height
		for(int j = 0;j < n;j += m)
		{
			// w = 1;
			complexnum w; w.set(1,0);
			for(int k = 0;k < m/2;k++)
			{
				// set P(x) = u(x) + w*v(x);
				complexnum u = a[j+k];
				complexnum v = a[j+m/2+k];
				v.mul(w);

				a[j+k] = u+v;
				a[j+m/2+k] = u-v;
				w.mul(wm);
			}
		}
	}
}

int fft(int n)
{
	// raise n to power of 2, then mul by 2;
	int lgn = 1;
	while((1<<lgn) < n){lgn++;}
	lgn++;
	for(int i = n;i < (1<<lgn);i++)
	{
		a[i].set(0,0);
		b[i].set(0,0);
	}

	n = (1<<lgn);
	// conversion from cofficient to point-value form;
	dft(a,1,n);
	dft(b,1,n);


	// point-wise multiply
	for(int i = 0;i < n;i++)
	{
		a[i].mul(b[i]);
	}


	// conversion from point-value to cofficient form;
	dft(a,-1,n);

	
	// taking avg
	for(int i = 0;i < n;i++)
	{
		a[i].real /= n;
	}


	// rounding off
	for(int i = 0;i < n;i++)
	{
		a[i].real = round(a[i].real);
		a[i].imag = 0;
	}

	return n;
}