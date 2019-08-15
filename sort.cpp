

const int limiter = 512;
const int radsize = 10;
const int arrsize = 100;
type tarr[arrsize];

// define radlen for arrtyp
// define radix(arrtyp,k) for arrtyp, return int
template<class type> void insertionsort(type *arr,int p,int r)
{
	for(int i = p;i < r;i++)
	{
		type ai = arr[i];
		int j = i-1;
		while(j >= p && ai < arr[j]){arr[j+1]=arr[j];j--;}
		arr[j+1] = ai;
	}
}

template<class type> void merge(type *arr,int p,int q,int r)
{
	int i1 = p, i2 = q;
	for(int i = 0;i < r-p;i++)
	{
		if(i2 >= r || (i1 < q && arr[i1] < arr[i2])){tarr[i] = arr[i1++];}
		else{tarr[i] = arr[i2++];}
	}

	for(int i = 0;i < r-p;i++){arr[p+i] = tarr[i];}
}

template<class type> void mergesort(type *arr,int p,int r)
{
	if(r-p > limiter)
	{
		int q = (p+r)/2;

		mergesort(arr, p, q);
		mergesort(arr, q, r);
		merge(arr, p, q, r);

	}else
	{
		insertionsort<type>(arr, p, r);
	}
}

template<class type> void quicksort(type *arr,int p,int r)
{
	if(r-p > limiter)
	{
		swap(arr[(p+r)/2], arr[r-1]);
		type hing = arr[r-1];
		int il = p;
		int ih = r-1;
		
		// pivot around hing
		for(int i = p;i < ih;i++)
		{
			if(arr[i] < hing){swap(arr[i],arr[il]);il++;}
			else if(arr[i] == hing){swap(arr[i],arr[ih-1]);ih--;i--;}
		}
		// relocate hing value in sorted order
		for(int i = 0;i < r-ih;i++)
		{
			swap(arr[il+i], arr[ih+i]);
		}

		quicksort<type>(arr, p, il);
		quicksort<type>(arr, il+(r-ih), r);
	}
	else{insertionsort<type>(arr, p, r);}
}


int countarr[radsize];

// functions to be maually defined accordinly of type;
int radix(type,int);
int radlen(type);


template<class type> void countsort(type *arr,int p,int r,int k=0)
{
	// set to zero
	for(int i = 0;i < radsize;i++){countarr[i] = 0;}
	// find count of all radix values
	for(int i = p;i < r;i++){countarr[radix(arr[i], k)]++;}

	// find end-index of all values
	for(int i = 1;i < radsize;i++){countarr[i] += countarr[i-1];}
	// place all values accordingly of end-index
	for(int i = r-1;i >= p;i--){tarr[countarr[radix(arr[i], k)]-1] = arr[i];countarr[radix(arr[i], k)]--;}
	// copy sorted array into original array
	for(int i = 0;i < r-p;i++){arr[i+p] = tarr[i];}
}

template<class type> void radixsort(type *arr,int p,int r)
{
	int k = 0;
	// find max rad length
	for(int i = p;i < r;i++)
	{
		if(k < radlen(arr[i])){k = radlen(arr[i]);}
	}
	
	// sort according to radix index
	for(int l = 0;l < k;l++)
	{
		countsort<type>(arr, p, r, l);
	}
}
