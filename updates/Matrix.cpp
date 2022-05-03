
struct DiscreteMatrix {

    static const int64_t mod = 1e9 + 7;

    int64_t *arr = 0;
    int n, m; 

    DiscreteMatrix(int N, int M) {
        n = N; m = M;
        arr = new int64_t[n * m];
        fill(arr, arr + n * m, 0);
    }

    DiscreteMatrix(const DiscreteMatrix &arg) {
        n = arg.n; m = arg.m;
        arr = new int64_t[n * m];
        copy(arg.arr, arg.arr + n * m, arr);
    }

    ~DiscreteMatrix() {
        if(arr == 0){return;}
        delete [] arr;
    }

    int64_t& operator()(const int& i1, const int& i2) {
        assert(i1 < n);
        assert(i2 < m);
        return arr[(i1 * m) + i2];
    }

    int64_t& operator()(const int& i1, const int& i2) const {
        assert(i1 < n);
        assert(i2 < m);
        return arr[(i1 * m) + i2];
    }

    DiscreteMatrix operator=(const DiscreteMatrix& arg) {
        n = arg.n; m = arg.m;
        if(arr != 0){delete [] arr; arr = 0;}

        arr = new int64_t[n * m];
        copy(arg.arr, arg.arr + n * m, arr);

        return *this;
    }

    static DiscreteMatrix Identity(int s) {
        DiscreteMatrix mat(s, s);

        for(int i = 0; i < s; i++) {
            mat(i,i) = 1;
        }

        return mat;
    }

    friend DiscreteMatrix operator+(const DiscreteMatrix &a1, const DiscreteMatrix &a2) {
        assert(a1.n == a2.n);
        assert(a1.m == a2.m);

        DiscreteMatrix res(a1.n, a1.m);
        for(int i = 0; i < a1.n * a1.m; i++) {
            res.arr[i] = (a1.arr[i] + a2.arr[i]) % mod;
        }

        return res;
    }


    friend DiscreteMatrix operator-(const DiscreteMatrix &a1, const DiscreteMatrix &a2) {
        assert(a1.n == a2.n);
        assert(a1.m == a2.m);

        DiscreteMatrix res(a1.n, a1.m);
        for(int i = 0; i < a1.n * a1.m; i++) {
            res.arr[i] = (a1.arr[i] + mod - a2.arr[i]) % mod;
        }

        return res;
    }


    friend DiscreteMatrix operator*(const DiscreteMatrix &a1, const DiscreteMatrix &a2) {
        assert(a1.m == a2.n);

        DiscreteMatrix res(a1.n, a2.m);
        for(int i = 0; i < a1.n; i++) {
            for(int j = 0; j < a2.m; j++) {
                for(int k = 0; k < a1.m; k++) {
                    res(i,j) = (res(i,j) + (a1(i,k) * a2(k,j) % mod)) % mod;
                }
            }
        }

        return res;
    }

    DiscreteMatrix exp(int64_t e) {

        assert(n == m);

        if(e < 0) {e = -e; e = (mod-2) * e % mod;}
        e %= mod-1;

        DiscreteMatrix base = *this;
        DiscreteMatrix res = Identity(n);
        while(e > 0) {
            if(e & 1){res = res * base;}
            base = base * base;
            e >>= 1;
        }

        return res;
    }

    friend ostream& operator<<(ostream& os, const DiscreteMatrix& arg) {
        for(int i = 0; i < arg.n; i++) {
            for(int j = 0; j < arg.m; j++) {
                os << (int)arg(i,j);
                os << " ";
            }
            os << "\n";
        }

        return os;
    }
};