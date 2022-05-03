
int64_t Exp(int64_t base, int64_t exp, int64_t mod) {

    if(exp < 0){exp = -exp; exp = (mod-2) * exp % (mod-1);}
    exp %= (mod-1);

    int64_t res = 1;
    while(exp > 0){
        if(exp & 1){res = res * base % mod;}
        base = base * base % mod;
        exp >>= 1;
    }

    return res;
}


struct { // extendedEuclic, GCD, MillerRabin

    int64_t gcd(int64_t a, int64_t b) {
        a = abs(a);
        b = abs(b);
        if(min(a,b) == 0){
            return max(a,b);
        }

        int64_t c;
        while(a%b){
            c = a%b;
            a = b;
            b = c;
        }

        return b;
    }

    pair<int64_t, int64_t> extendedEuclid(int64_t A, int64_t B) {
        A = abs(A);
        B = abs(B);

        if(min(A,B) == 0){
            return pair<int64_t, int64_t> (0,0);
        }

        int64_t p1 = 1;
        int64_t q1 = 0;
        int64_t p2 = 0;
        int64_t q2 = 1;

        if(A < B) {
            p1 = 0;
            q1 = 1;
            p2 = 1;
            q2 = 0;
        }

        while(true) {
            int64_t a = A*p1 + B*q1;
            int64_t b = A*p2 + B*q2;

            if(a%b == 0){
                return pair<int64_t, int64_t>(p2, q2);
            }
            
            int64_t i = a/b;
            int64_t x1 = p1 - i*p2;
            int64_t x2 = q1 - i*q2;

            p1 = p2;
            q1 = q2;
            p2 = x1;
            q2 = x2;
        }
    }


    int64_t Exp(int64_t base, int64_t exp, int64_t mod) {

        if(exp < 0){exp = -exp; exp = (mod-2) * exp % (mod-1);}
        exp %= (mod-1);

        int64_t res = 1;
        while(exp > 0){
            if(exp & 1){res = res * base % mod;}
            base = base * base % mod;
            exp >>= 1;
        }

        return res;
    }


    bool check_composite(int64_t n, int64_t a, int64_t d, int s) {
        int64_t x = Exp(a, d, n);
        if (x == 1 || x == n - 1)
            return false;
        for (int r = 1; r < s; r++) {
            x = x * x % n;
            if (x == n - 1)
                return false;
        }
        return true;
    }


    bool MillerRabin(int64_t n) { // returns true if n is prime, else returns false.
        if (n < 2)
            return false;

        int r = 0;
        int64_t d = n - 1;
        while ((d & 1) == 0) {
            d >>= 1;
            r++;
        }

        for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
            if (n == a)
                return true;
            if (check_composite(n, a, d, r))
                return false;
        }
        return true;
    }
} NumTh;


struct SIEVE { // primes, minDivisor

    static const int64_t prmSize = 1 << 17;
    static const int64_t bitSize = 1 << 20;

    int primes[prmSize];
    int minDivisor[bitSize];
    char bits[bitSize];
    int plen = 0;

    SIEVE(int64_t prmSizeArg, int64_t bitSizeArg) {
        assert(prmSizeArg < this->prmSize);
        assert(bitSizeArg < this->bitSize);

        minDivisor[1] = 1;
        minDivisor[0] = 1;
        for(int64_t i = 2; i < bitSize; i++){
            if(bits[i]){continue;}

            primes[plen++] = i;
            for(int64_t j = 1; i*j < bitSize; j++){
                bits[i*j] = 1;

                if(minDivisor[i*j] == 0){
                    minDivisor[i*j] = i;
                }
            }
        }
    }

    // bool isRoot(int64_t a, int64_t p) {

    //     int64_t p2 = p-1;
    //     while(p2 > 1) {

    //         int64_t d = minDivisor[p2];
    //         while(p2 % d == 0){
    //             p2 /= d;
    //         }

    //         if(Exp(a, (p-1)/d, p) == 1){
    //             return false;
    //         }
    //     }
    //     return true;
    // }

} Sieve(100000, 1000000); // primeLen, arrLEn


struct COMB { // choose, permutation, factorial

    static const int64_t mod = 998244353L;
    static const int size = 1 << 20;
    

    int64_t fact[size];
    int64_t ifact[size];
    bool factConstructed = false;
    bool ifactConstructed = false;
    
    COMB(int sizeArg, const int64_t modArg) {
        assert(this->size > sizeArg);
        assert(this->mod == modArg);
    }

    void constructFact() {
        fact[0] = 1;
        for(int64_t i = 1; i < size; i++){
            fact[i] = fact[i-1] * i % mod;
        }
        factConstructed = true;
    }
    
    void constructiFact() {
        ifact[0] = 1;
        for(int64_t i = 1; i < size; i++){
            ifact[i] = ifact[i-1] * Exp(i, mod-2) % mod;
        }
        ifactConstructed = true;
    }

    int64_t Exp(int64_t base, int64_t exp) {
    
        if(exp < 0){exp = -exp; exp = (mod-2) * exp % (mod-1);}
        exp %= (mod-1);

        int64_t res = 1;
        while(exp > 0){
            if(exp & 1){res = res * base % mod;}
            base = base * base % mod;
            exp >>= 1;
        }

        return res;
    }

    int64_t choose(int n, int r) {

        if(r > n) {return 0;}
        if(n < 0) {return 0;}

        if(!factConstructed){constructFact();}
        if(!ifactConstructed){constructiFact();}

        int64_t num = fact[n];
        int64_t den = ifact[n-r] * ifact[r] % mod;
        return num * den % mod;
    }

    int64_t permutation(int n, int r) {

        if(r > n) {return 0;}
        if(n < 0) {return 0;}

        if(!factConstructed){constructFact();}
        if(!ifactConstructed){constructiFact();}

        int64_t num = fact[n];
        int64_t den = fact[r];
        return num * den % mod;
    }

    int64_t factorial(int n) {

        if(n < 0) {return 0;}
        if(!factConstructed){constructFact();}

        return fact[n];
    }
} Comb(1000000, 998244353); // arrLen, mod


struct DISCRETELOG { // discreteLog

    unordered_map<int64_t,int> powers;

    int64_t Exp(int64_t base, int64_t exp, int64_t mod) {

        if(exp < 0){exp = -exp; exp = (mod-2) * exp % (mod-1);}
        exp %= (mod-1);

        int64_t res = 1;
        while(exp > 0){
            if(exp & 1){res = res * base % mod;}
            base = base * base % mod;
            exp >>= 1;
        }

        return res;
    }


    int64_t discreteLog(int64_t a, int64_t b, int64_t p, int64_t nroot) {

        powers.clear();

        int64_t base = 1;
        int64_t inc = Exp(a, nroot, p);

        for(int64_t i = 0; i <= p; i += nroot) {
            powers[base] = i;
            base = base * inc % p;
        }


        int64_t dec = Exp(a, -1, p);
        
        int k = 0;
        int64_t curr = b;
        while(powers.find(curr) == powers.end()) {
            curr = curr * dec % p;
            k++;
        }

        return powers[curr] + k;
    }
} disCreteLog;

