
// dft(arr, size, inv);
const double pi = 22.0/7;
struct FFT { // dft

    static const int64_t sizeLg = 21;
    
    complex<double> nroot[sizeLg];
    complex<double> nrootInv[sizeLg];
    
    FFT(int64_t size) {
        assert(size < (1 << this->sizeLg));
        
        nroot[sizeLg-1] = complex<double>(cos(2.0 * pi/(1 << (sizeLg-1))), sin(2.0 * pi/(1 << (sizeLg-1))));
        nrootInv[sizeLg-1] = complex<double>(cos(-2.0 * pi/(1 << (sizeLg-1))), sin(-2.0 * pi/(1 << (sizeLg-1))));
        for(int64_t i = sizeLg-2; i >= 0; i--) {
            nroot[i] = nroot[i+1] * nroot[i+1];
            nrootInv[i] = nrootInv[i+1] * nrootInv[i+1];
        }
    }
    
    int revi(int i, int lgn) {
        int ri = 0;
        while(lgn-- > 0){
            ri <<= 1;
            ri |= (i & 1);
            i >>= 1;
        }
        return ri;
    }


    void dft(complex<double> *arr, int size, bool inv) {
        
        int lgn = log2(size);
        for(int i = 0; i < size; i++) {
            int ri = revi(i, lgn);
            if(i < ri){swap(arr[i], arr[ri]);}
        }

        complex<double> wm, w;
        complex<double> u, v;

        for(int s = 2, si = 1; s <= size; s *= 2, si++) {
            wm = inv ? nrootInv[si] : nroot[si];
            for(int i = 0; i < size; i += s) {
                w = 1;
                for(int j = 0; j < s/2; j++) {

                    u = arr[i + j];
                    v = w * arr[i + j + s/2];

                    arr[i + j] = u + v;
                    arr[i + j + s/2] = u - v;

                    w *= wm;
                }
            }
        }

        if(inv) {
            for(int i = 0; i < size; i++) {
                arr[i] = round(arr[i].real()/size);
            }
        }
    }
} fft(100000); // arrLen


// dft(arr, size, inv);
struct NFT { // dft

    static const int64_t size = (1L << 23);
    static const int64_t mod = 998244353L;
    static const int64_t gen = 3L;
    
    int64_t nroot[40];
    int64_t nrootInv[40];
    
    NFT(int64_t sizeArg, int64_t modArg, int64_t genArg) {
        assert(sizeArg < this->size);
        assert(modArg == this->mod);
        assert(genArg == this->gen);
        
        int64_t lgn = log2(size);
        nroot[lgn] = Exp(gen, (mod-1)/size);
        nrootInv[lgn--] = Exp(gen, -(mod-1)/size);
        
        
        while(lgn >= 0){
            nroot[lgn] = nroot[lgn+1] * nroot[lgn+1] % mod;
            nrootInv[lgn] = nrootInv[lgn+1] * nrootInv[lgn+1] % mod;
            lgn--;
        }
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

    int revi(int i, int lgn) {
        int ri = 0;
        while(lgn-- > 0){
            ri <<= 1;
            ri |= (i & 1);
            i >>= 1;
        }
        return ri;
    }

    void dft(int64_t *arr, int size, bool inv) {
        
        int lgn = log2(size);
        for(int i = 0; i < size; i++) {
            int ri = revi(i, lgn);
            if(i < ri){swap(arr[i], arr[ri]);}
        }

        int64_t wm, w;
        int64_t u, v;

        for(int s = 2, si = 1; s <= size; s *= 2, si++) {
            wm = inv ? nrootInv[si] : nroot[si];
            for(int i = 0; i < size; i += s) {
                w = 1;
                for(int j = 0; j < s/2; j++) {

                    u = arr[i + j];
                    v = w * arr[i + j + s/2] % mod;

                    arr[i + j] = (u + v) % mod;
                    arr[i + j + s/2] = (u + mod - v) % mod;

                    w = w * wm % mod;
                }
            }
        }

        if(inv) {
            for(int i = 0; i < size; i++) {
                arr[i] = arr[i] * Exp(size, -1) % mod;
            }
        }
    }
} nft(100000, 998244353L, 3L); // arrLen, prime, generator