

// fendwick tree
const int size = 100;

template<typename type> class fendwick{
public:

type arr[size];
type fen[size];
int n;
type zero;
type merge(type arg1, type arg2)
{
	// merge code here
	return arg1+arg2;
}
void update(type v,int i)
{
	while(i > 0 && i <= n)
	{
		fen[i] = merge(fen[i], v);
		i -= (i&-i);
	}
}
void set()
{
	for(int i = 1;i <= n;i++)
	{
		update(arr[i], i);
	}
}
type query(int l,int r)
{
	if(r > l){return zero;}
	int r2 = l+(l&-l)-1;
	if(r2 == r){return fen[l];}
	else if(r2 < r){return merge(fen[l], query(r2+1, r));}
	else{return merge(arr[l], query(l+1, r));}
}

};