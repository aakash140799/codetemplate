


uint64_t stringHash(const string &s) {

    const uint64_t m1 = 1e9 + 7;
    const uint64_t p1 = 31;

    const uint64_t m2 = 998244353;
    const uint64_t p2 = 37;

    uint64_t h1 = 0;
    uint64_t h2 = 0;

    uint64_t p1i = 1;
    uint64_t p2i = 1;

    for(char c : s) {
        h1 = (h1 + (p1i * (uint64_t)(c - 'a') % m1)) % m1;
        h2 = (h2 + (p2i * (uint64_t)(c - 'a') % m2)) % m2;
        
        p1i = p1i * p1 % m1;
        p2i = p2i * p2 % m2;
    }
    
    return h1 * (uint64_t)1e10 + h2;
}


struct PrefixFunc { // mkae_dfa, run_dfa, pass (action(i, len))

    static const int size = 1 << 18;

    string pat;
    string str;
    int preLen[size];
    
    PrefixFunc(int sizeArg) {
        assert(size > sizeArg);
    }

    void make_dfa(const string &patArg, void action(int i, int plen)) {

        pat = "#" + patArg;

        preLen[0] = 0;
        preLen[1] = 0;
        action(1, 0);

        int index = 1;
        int matched = 0;
        while(index < pat.size()-1) 
        {
            if(matched > 0 && pat[index+1] != pat[matched+1]) {
                matched = preLen[matched];
            }
            else if(matched == 0 && pat[index+1] != pat[matched+1]) {
                preLen[index+1] = 0;
                action(index+1, 0);

                index++;
                matched = 0;
            }
            else {
                preLen[index+1] = matched+1;
                action(index+1, matched+1);

                index++;
                matched++;
            }
        }
    }


    void run_dfa(const string &strArg, void action(int i, int plen)) {

        str = "#" + strArg;

        int index = 0;
        int matched = 0;
        while(index < str.size()-1) 
        {
            if(matched > 0 && str[index+1] != pat[matched+1]) {
                matched = preLen[matched];
            }
            else if(matched == 0 && str[index+1] != pat[matched+1]) {
                action(index+1, 0);
                index++;
                matched = 0;
            }
            else {
                action(index+1, matched+1);
                index++;
                matched++;
            }
        }
    }
};