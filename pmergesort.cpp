



const int limit = 512;
// first-index search, returns index of val equal to or grater than k
template<class type> int binarysearch(type *arr, int p,int r,type k)
{
	int i = p;
 	if(p == r){i = p;}
 	else if(k <= arr[p]){i = p;}
 	else if(arr[r-1] < k){i = r;}
 	else
 	{
 		while(r-p > 1)
 		{
 			int q = (p+r)/2;
 			if(k <= arr[q]){r = q;}
 			else if(arr[q] < k){p = q;}
 		}

 		i = r;
 	}

 	return i;
}

// parallel merge 
template<class type> void merge(type *arr1, type *arr3, int p1, int r1, int p2, int r2, int p3)
{
 	int n1 = r1-p1;
 	int n2 = r2-p2;
 	if(n1 < n2)
 	{
 		swap(p1, p2);
 		swap(r1, r2);
 		swap(n1, n2);
 	}
 	if(n1 == 0){return;}
 	else
 	{
 		int q1 = (p1+r1)/2;
 		int q2 = binarysearch<type>(arr1, p2, r2, arr1[q1]);
 		int e1 = q1-p1;
 		int e2 = q2-p2;

 		arr3[p3+e1+e2] = arr1[q1];
 		//if(q1-p1 > 0){merge(arr1, arr3, p1, q1, p2, q2, p3);}
 		//if(r1-q1-1 > 0){merge(arr1, arr3, q1+1, r1, q2, r2, p3+e1+e2+1);}
 		merge<type>(arr1, arr3, p1, q1, p2, q2, p3);	// thread1
 		merge<type>(arr1, arr3, q1+1, r1, q2, r2, p3+e1+e2+1);	// thread2
 		// thread join
 	}
}
// parallel merge sort using parallel merge and 
template<class type> void mergesort(type *arr1, type *arr2, int p1, int r1, int p2)
{
 	if(r1-p1 > limit)
 	{
 		int q1 = (p1+r1)/2;
 		type *t = new type[r1-p1+1];


 		mergesort<type>(arr1, t, p1, q1, 0);	// thread1
 		mergesort<type>(arr1, t, q1, r1, q1-p1);	// thread2
 		// thread join
 		merge<type>(t, arr2, 0, q1-p1, q1-p1, r1-p1, p2);
 		delete[] t;
 	}
 	else
 	{
 		// base case using insertion sort
 		for(int i = 0;i < r1-p1;i++){arr2[i+p2] = arr1[i+p1];}
 		for(int i = 0;i < r1-p1;i++)
 		{
 			type t = arr2[i+p2];
 			int j = i-1;

 			while(j >= 0 && t < arr2[j+p2])
 			{
 				arr2[j+1+p2] = arr2[j+p2];
 				j--;
 			}
 			arr2[j+1+p2] = t;
 		}
 	}
}
