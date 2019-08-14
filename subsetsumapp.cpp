


// a - array of value
// subset - array of subset-sum values
// t - used by merge for merging
uint64_t a[100], subset[100], t[100];
uint64_t sum;

// merge operation which merges a[1-n] and a[1-n]+k
int merge(uint64_t *a,int k,int n)
{
	int index1 = 0;
	int index2 = 0;
	int c = 0;
	while(index1 < n || index2 < n)
	{
		if(index2 > n || (index1 < n && a[index1] < a[index2]+k))
		{
			t[c++] = a[index1++];
		}
		else
		{
			if(a[index2]+k < sum){t[c++] = a[index2]+k;}
			index2++;
		}
	}

	for(int i = 0;i < c;i++){a[i]=t[i];}

	return c;
}


// remove close-distant values, using del value
int trim(uint *a,float del,int n)
{
	int l = 1;
	for(int i = 1;i < n;i++)
	{
		if((float)a[i] > (float)a[l-1]*(1+del)){a[l] = a[i];l++;}
	}
	return l;
}

// subset-sum approximation algorithm using del value
int subsetsum(float del,int n)
{
	// initliase subset-sum to zero
	subset[0] = 0;

	// size of current subset
	int ns = 1;

	// iterate over all value in array
	for(int i = 0;i < n;i++)
	{
		// merge current subset-values and current-subset-values+k
		ns = merge(subset, a[i], ns);
		// remove close distant value, keeping lowest value
		ns = trim(subset, del, ns);
	}
	// return max subset-sum value
	return subset[ns-1];
}