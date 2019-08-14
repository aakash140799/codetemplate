

// define max heap - mheap//
template<type> int median(type *arr,int n)
{
	// half fill the heap
	for(int i = 0;i < n/2;i++)
	{
		mheap.push(arr[i]);
	}

	// remove all value greater than half the array;
	for(int i = n/2;i < n;i++)
	{
		mheap.push(arr[i]);
		mheap.pop();
	}

	return heap.top();
}