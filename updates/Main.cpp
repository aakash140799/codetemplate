


#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
int128_t(319435266158123073073250785136463577088) // 128 bit integer
cpp_int // arbitrary bit integer



GCC/CLang
__int128 // 128 bit integer, print, read needs defining



#define sumFunc [](int64_t l, int64_t r) -> int64_t {return l + r;}
#define ithFunc [](int i) -> int64_t {return i <= 10 ? i : 0;}
#define mulFunc [](int64_t l, int64_t r) -> int64_t {return l * r % mod;}
#define maxFunc [](int64_t l, int64_t r) -> int64_t {return max(l, r);}
#define minFunc [](int64_t l, int64_t r) -> int64_t {return min(l, r);}


const int64_t prime = 1e9 + 7;
const int64_t prime = 998244353;
const int64_t prime = 2,500,000,001;
const int64_t bigPrime = 165678739293946997L;







int countBits(int64_t i) {
        int c = 0;
        while(i > 0) {
            c += (i & 1);
            i >>= 1;
        }
        return c;
}



