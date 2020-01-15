
// matrix class

template<typename type> class matrix
{
	public:
	type *dat;
	int nr, nc;

	// utility variables
	int n, m;
	type nul;
	type zero;
	bool trans;
	bool nulmat;

	// initialise matrix
	matrix(int narg=1,int marg=1,bool matarg = false)
	{
		nr = n = narg;
		nc = m = marg;
		dat = new type[n*m +4];

		trans = false;
		nulmat = matarg;
	}

	// reference operator with bound check, but no error return
	type &operator[][](int narg,int marg)
	{
		nul = zero;
		if(nulmat){return nul;}
		if(trans){swap(narg,marg);}
		if(narg < n && marg < m){return dat[narg*m + marg];}
		else{return nul;}
	}

	
	// return memory-based copy of matrix
	matrix<type> copy()
	{
		matrix<type> t(nr,nc,matarg);
		for(int l = 0;l < nr*nc;l++)
		{
			if(!trans){t.dat[l] = dat[l];}
			else{t.dat[l] = dat[(l%m)*m + (l/m)]}
		}

		return t;
	}

	
	// take representation based, transpose
	void transpose()
	{
		trans ^= 1;
		swap(nr, nc);
	}

	
	// memory based matrix multiplication
	friend matrix<type> operator*(matrix<type> arg1,matrix<type> arg2)
	{
		if(arg1.nc != arg2.nr){return matrix<type>(1,1,true);}
		matrix<type> res(arg1.nr,arg2.nc);

		for(int i = 0;i < arg1.nr;i++)
		{
			for(int j = 0;j < arg2.nc;j++)
			{
				res[i][j] = zero;
				for(int k = 0;k < arg1.nr;k++)
				{
					res[i][j] += arg1[i][k]*arg2[k][j];
				}
			}
		}

		return res;
	}

	// memory based matrix addition
	friend matrix<type> operator+(matrix<type> arg1,matrix<type> arg2)
	{
		if(arg1.nr != arg2.nr || arg1.nc != arg2.nc){return matrix<type>(1,1,true);}

		matrix<type> res(arg1.nr,arg1.nc);
		for(int i = 0;i < arg1.nr;i++)
		{
			for(int j = 0;j < arg1.nc;i++)
			{
				res[i][j] = arg1[i][j]+arg2[i][j];
			}
		}
	}


	// memory based dot product(with distribution)
	friend matrix<type> operator^(matrix<type> arg1,matrix<type> arg2)
	{
		if(arg2.nr%arg1.nr != 0 || arg2.nc%arg1.nc != 0){return matrix<type>(1,1,true);}
		matrix<type> res(arg2.nr,arg2.nc);
		for(int i = 0;i < arg2.nr;i++)
		{
			for(int j = 0;j < arg2.nc;j++)
			{
				res[i][j] = arg1[(i%arg1.nr)][(j%arg1.nc)]*arg2[i][j];
			}
		}
	}

	// memory based distributive addition
	friend matrix<type> operator&(matrix<type> arg1,matrix<type> arg2)
	{
		if(arg2.nr%arg1.nr != 0 || arg2.nc%arg1.nc != 0){return matrix<type>(1,1,true);}
		matrix<type> res(arg2.nr,arg2.nc);
		for(int i = 0;i < arg2.nr;i++)
		{
			for(int j = 0;j < arg2.nc;j++)
			{
				res[i][j] = arg1[(i%arg1.nr)][(j%arg1.nc)]*arg2[i][j];
			}
		}
	}
}