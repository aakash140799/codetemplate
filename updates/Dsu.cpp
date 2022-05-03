#include <iostream>
#include <queue>
#include <set>
#include <list>
#include <stack>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;


// always clear(n) before use
// getRoot(a)
// merge(a, b)
// gpCount
struct Dsu{

    const static int Asize = 1 << 19;

    Dsu(int sizeArg) {
        assert(sizeArg < Asize);
    }


    int par[Asize];
    int size[Asize];
    int gpCount;

    void clear(int n) {
        gpCount = n;
        fill(par, par+n+1, 0);
        fill(size, size+n+1, 0);
    }

    int getRoot(int a)
    {
        int t = a;
        while(par[t]){
            t = par[t];
        }

        while(par[a]){
            int pa = par[a];
            par[a] = t;
            a = pa;
        }

        return a;
    }

    bool merge(int a, int b) 
    {
        cout << a << " " << b << "\n";
        a = getRoot(a);
        b = getRoot(b);

        if(a != b) {
            if(size[a] > size[b]){
                par[b] = a;
            }
            else if(size[b] > size[a]){
                par[a] = b;
            }
            else{
                par[b] = a;
                size[a]++;
            }
            gpCount--;
            return true;
        }
        return false;
    }
};
Dsu dsu(3e5);