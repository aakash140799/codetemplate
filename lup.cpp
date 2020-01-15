

const size = 100;


// Ax = b;
// PA = LU
// LUx = Pb
float A[size][size], b[size], L[size][size], U[size][size], y[size], x[size]; int phi[size];

// decompose A into L, and U, such that PA = LU
void LUP_decompose(int n)
{
	// set initial P , in phi
	for(int i = 0;i < n;i++){phi[i]=i;}

	// iterates for 0 to n-1 submatrix
	for(int k = 0;k < n;k++)
	{
		// selects row with max valued element
		float akk = max(A[k][k],-A[k][k]);
		int ik = k;
		for(int i = k+1;i < n;i++)
		{
			if(max(A[i][k],-A[i][k]) > akk)
			{
				akk = max(A[i][k],-A[i][k]);
				ik = i;
			}
		}

		// swaps row with max valued element
		for(int j = 0;j < n;j++){swap(A[k][j],A[ik][j]);}
		swap(phi[k],phi[ik]);

		// set w, and v vector. 
		for(int i = k+1;i < n;i++)
		{
			A[i][k] /= akk;
			for(int j = k+1;j < n;j++)
			{
				A[i][j] -= A[i][k]*A[k][j];
			}
		}
	}

	// fill value in L, and U
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			if(i > j){L[i][j] = A[i][j]; U[i][j] = 0;}
			else if(i == j){L[i][j] = 1; U[i][j] = A[i][j];}
			else{ L[i][j] = 0; U[i][j] = A[i][j];}
		}
	}
}


// solve linear equalities by LUP_decomosition
void LUP_solve(int n)
{
	// decomose A into L, U;
	LUP_decompose(n);
	// now Ax = b;
	// LUx = Pb;
	// Ly = Pb; Ux = y;

	// solve Ly = Pb;
	for(int i = 0;i < n;i++)
	{
		y[i] = b[phi[i]];
		for(int j = 0;j < i;j++)
		{
			y[i] -= L[i][j]*y[j];
		}
	}
	// solve Ux = y;
	for(int i = n-1;i >= 0;i--)
	{
		x[i] = y[i];
		for(int j = n-1;j > i;j--)
		{
			x[i] -= U[i][j]*x[j];
		}
		x[i] /= U[i][i];
	}
}