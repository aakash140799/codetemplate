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



// clear(n, identity)
// update(i, T updateFunc(T))
// query(R, T merge(T, T))
// 1-based indexing
// TESTED
// ALWAYS clear before use
template<class T> struct FendWick {

    static const int size = 1 << 18;
    T identity;

    T arr[size];
    int n;

    FendWick(int sizeArg) {
        assert(sizeArg < size);
    }

    void clear(int nArg, T identityArg) {
        n = nArg;
        identity = identityArg;
        fill(arr, arr+size, identity);
    }
    
    void update(int i, T updateFunc(T)) {
        while(i <= n) {
            arr[i] = updateFunc(arr[i]);
            i += i & -i;
        }
    }

    T query(int R, T merge(T, T)) {

        T sum = identity;
        while(R > 0){
            sum = merge(sum, arr[R]);
            R -= R & -R;
        }
        
        return sum;
    }
};
FendWick<int64_t> fendWick(200000);
