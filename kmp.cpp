


// arr contains index of match found//
int arr[100];
// phi is set by algorithm according to dfa of pattern string
int phi[100];
// set phi according to dfa of pattern string, such that phi[i] = len of pattern matching having suffix len less i;
void makepattern(sting p)
{
	int n = p.size();
	phi[0] = -1;
	int k = -1;

	for(int i = 1;i < n;i++)
	{
		while(k > -1 && p[k+1] != p[i])
		{
			k = phi[k];
		}
		if(p[k+1] == p[i])
		{
			k++;
		}
		phi[i] = k;
	}
}

// Knuth-Morris-Prat algorithm using dfa
int knp(string s,string p)
{
	// make dfa of string
	makepattern(p);
	
	// no of match found
	int c = 0;

	int ns = s.size();
	int np = p.size();
	
	// index of phi matched till now
	int k = -1;

	// iterate for string s
	for(int i = 0;i < ns;i++)
	{
		// while pattern do not match, decrease k to last possibly matching pattern len;
		while(k > -1 && p[k+1] != s[i])
		{
			k = phi[k];
		}
		// when match found, increase len pf phi matched
		if(p[k+1] == s[i])
		{
			k++;
		}
		// if full string p matched, add starting index.
		if(k == np-1)
		{
			arr[c++] = i-k;
			k = phi[k];
		}
	}

	// return len of indexes of pattern matched.
	return c;
}