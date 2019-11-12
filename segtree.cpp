


const int size = 100000;
template<classname type> class seg
{
	public:
	type arr[size];
	int upd[size];
	int s = 0, e = 0,len = 0;


	type nil;
	type (*updfunc)(type arg,int s,int e);
	type (*megfunc)(type arg1,type arg2);


	void set(int n,type *tarr)
	{
		s = 0;
		e = 0;
		len = 1;
		while(len < n)
		{
			s = (s<<1)+1;
			e = (e<<1)+2;
			len <<= 1;
		}
		for(int i = s;i <= e;i++)
		{
			if(i-s < n){arr[i] = tarr[i-s];}
			else{arr[i] = nil;}
		}
		for(int i = s-1;i >= 0;i--)
		{
			arr[i] = megfunc(arr[(i<<1)+1], arr[(i<<1)+2]);
		}
	}


	type query(int l,int r,int s = 1,int e = len,int i = 0)
	{
		if(r < s || e < l){return nil;}
		else if(l <= s && e <= r){return arr[i];}


		int m = (s+e)/2;
		if(r <= m)
		{
			return query(l, r, s, m, (i<<1)+1);
		}
		else if(m+1 <= l)
		{
			return query(l, r, m+1, e, (i<<1)+2);
		}
		else
		{
			return megfunc(query(l, r, s, m, (i<<1)+1), query(l, r, m+1, e, (i<<1)+2));
		}
	}

	void change(int x,int i)
	{
		seg[i] = x;
		while(i > 0)
		{
			i = (i-1)/2;
			seg[i] = megfunc(seg[(i<<1)+1], seg[(i<<1)+2]);
		}
	}

	void pushupd(int s,int e,int i)
	{
		if(s != e)
		{
			upd[(i<<1)+1] += upd[i];
			upd[(i<<1)+2] += upd[i];
		}

		while(upd[i] > 0)
		{
			seg[i] = updfunc(seg[i],s,e);
			upd[i]--;
		}
	}


	void update(int l,int r,int s = 1,int e = len,int i = 0)
	{
		if(r < s || e < l){return;}
		else if(l <= s && e <= r)
		{
			upd[i]++;
			pushupd(s, e, i);
			return;
		}


		int m = (s+e)/2;

		if(upd[i] > 0){pushupd(s, e, i);}
		if(r <= m)
		{
			update(l, r, s, m, (i<<1)+1);
		}
		else if(m+1 <= l)
		{
			update(l, r, m+1, e, (i<<1)+2);
		}
		else
		{
			update(l, r, s, m, (i<<1)+1);
			update(l, r, m+1, e, (i<<1)+2);
		}
		if(upd[(i<<1)+1]>0){pushupd(s, m, (i<<1)+1);}
		if(upd[(i<<1)+2]>0){pushupd(m+1, e, (i<<1)+2);}

		seg[i] = megfunc(seg[(i<<1)+1], seg[(i<<1)+2]);

	}
};