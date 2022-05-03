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



// make_seg(n, makeFunc(i), merge(T, T), identity)
// update(i, T, merge(T,T))
// query(l, r, merge(T,T))
// findIndex(bool chooseLeft(T))
// 1-based indexing
// ALWAYS use make_seg before use
// TESTED
template<class T> struct SegTree { 

    static const int size = 1 << 19;

    T seg[size];
    int s, e, len;

    T identity;

    

    SegTree(int sizeArg) {
        assert((1 << (int)(ceil(log2(sizeArg)) + 1)) <= size);
    }

    void make_seg(int n, T makeFunc(int i), T merge(T L, T R), T identityArg) {

        s = e = 0;
        len = 1;
        identity = identityArg;

        while(len < n) {
            s = (s << 1) + 1;
            e = (e << 1) + 2;
            len <<= 1;
        }

        for(int i = 1; i <= len; i++) {
            seg[i + s - 1] = makeFunc(i);
        }

        for(int i = s-1; i >= 0; i--) {
            seg[i] = merge(seg[(i<<1)+1], seg[(i<<1)+2]);
        }
    }

    void update(int i, T v, T merge(T L, T R)) {

        i += s-1;
        seg[i] = v;

        while(i > 0) {
            i = (i-1)/2;
            seg[i] = merge(seg[(i<<1)+1], seg[(i<<1)+2]);
        }
    }

    T query(int l, int r, int s, int e, int i, T merge(T L, T R)) {
        if(r < s || e < l){return identity;}
        else if(l <= s && e <= r) {return seg[i];}

        int m = (s+e)/2;
        return merge(query(merge, l, r, s, m, (i<<1)+1), 
                query(merge, l, r, m+1, e, (i<<1)+2));
    }

    T query(int l, int r, T merge(T L, T R)) {
        return query(l, r, 1, len, 0, merge);
    }

    int findIndex(int s, int e, int i, bool chooseLeft(T)) {
        if(s == e) {
            if(chooseLeft(seg[i])){return s;}
            return 0;
        }

        int m = (s + e) / 2;
        return chooseLeft(seg[(i<<1) + 1]) ? findIndex(s, m, (i<<1) + 1, chooseLeft) : findIndex(m+1, e, (i<<1) + 2, chooseLeft);
    }

    int findIndex(bool chooseLeft(T)) {
        return findIndex(1, this->len, 0, chooseLeft);
    }
};
SegTree<int> seg(200000); // arrLen




// make_seg(n, makeFunc, merge, identity, updIdentity)
// update(l, r, k, pushToUpd(k, upd[i], s, e))
// query(l, r, merge, pushToUpd(upd[i], upd[child], s_child, e_child), pushToSeg(upd[i], seg[i], s, e))
template<class T, class V> struct LazySegTree {

    static const int size = 1 << 19;

    T seg[size];
    V upd[size];
    int s, e, len;

    T identity;
    V updIdentity;


    LazySegTree(int sizeArg) {
        assert((1 << (int)(ceil(log2(sizeArg)) + 1)) <= size);
    }

    void make_seg(int n, T makeFunc(int i), T merge(T L, T R), T identityArg, V updIdentityArg) {

        s = e = 0;
        len = 1;
        identity = identityArg;
        updIdentity = updIdentityArg;

        while(len < n) {
            s = (s << 1) + 1;
            e = (e << 1) + 2;
            len <<= 1;
        }

        for(int i = 1; i <= len; i++) {
            seg[i + s - 1] = makeFunc(i);
            upd[i + s - 1] = updIdentity;
        }

        for(int i = s-1; i >= 0; i--) {
            seg[i] = merge(seg[(i<<1)+1], seg[(i<<1)+2]);
            upd[i] = updIdentity;
        }
    }

    void update(int l, int r, int s, int e, int i, V k, V pushToUpd(V,V,int,int)) {
        if(r < s || e < l){return;}
        else if(l <= s && e <= r){upd[i] = pushToUpd(k, upd[i], s, e);return;}

        int m = (s+e)/2;
        update(l, r, s, m, (i<<1)+1, k, pushToUpd);
        update(l, r, m+1, e, (i<<1)+2, k, pushToUpd);
    }

    void update(int l, int r, V k, V pushToUpd(V,V,int,int)) {
        update(l, r, 1, this->len, 0, k, pushToUpd);
    }

    T query(int l, int r, int s, int e, int i, T merge(T,T), V pushToUpd(V,V,int,int), T pushToSeg(V,T,int,int)) {
        seg[i] = pushToSeg(upd[i], seg[i], s, e);
        if(upd[i]!=updIdentity && (i<<1)+2 <= this->e){
            upd[(i<<1)+1] = pushToUpd(upd[i], upd[(i<<1)+1], s, (s+e)/2);
            upd[(i<<1)+2] = pushToUpd(upd[i], upd[(i<<1)+2], ((s+e)/2)+1, e);
        }
        upd[i] = updIdentity;

        if(r < s || e < l){return identity;}
        else if(l <= s && e <= r) {return seg[i];}

        int m = (s+e)/2;
        return merge(query(l, r, s, m, (i<<1)+1, merge, pushToUpd, pushToSeg), 
                query(l, r, m+1, e, (i<<1)+2, merge, pushToUpd, pushToSeg));
    }

    T query(int l, int r, T merge(T,T), V pushToUpd(V,V,int,int), T pushToSeg(V,T,int,int)) {
        return query(l, r, 1, this->len, 0, merge, pushToUpd, pushToSeg);
    }
};
LazySegTree<int64_t, int64_t> seg(200000); // arrLen



// make_grid(n, m, identity, makeFunc(i, j), T merge(T, T))
// query(li, lj, ri, rj, T merge(T,T), T unmerge(T, T))
template<class T> struct Grid {

    static const int nSize = 1002;
    static const int mSize = 1002;

    T arr[nSize][mSize];
    int n, m;
    T identity;

    Grid(int nArg, int mArg){
        assert(nArg < nSize);
        assert(mArg < mSize);
    }

    void make_grid(int nArg, int mArg, T identityArg, T makeFunc(int i, int j), T merge(T, T)) {
        assert(nArg < nSize);
        assert(mArg < mSize);

        n = nArg;
        m = mArg;
        identity = identityArg;

        for(int i = 1; i <= n; i++) {
            arr[i][0] = identity;
        }

        for(int j = 1; j <= m; j++) {
            arr[0][j] = identity;
        }

        for(int i = 1; i <= n; i++) {
            T dp = identity;
            for(int j = 1; j <= m; j++) {
                dp = merge(dp, makeFunc(i, j));
                arr[i][j] = merge(dp, arr[i-1][j]);
            }
        }
    }

    T query(int li, int lj, int ri, int rj, T merge(T, T), T unmerge(T, T)) {
        return unmerge(merge(arr[ri][rj], arr[li-1][lj-1]), merge(arr[li-1][rj],arr[ri][lj-1]));
    }
};
Grid<int64_t> grid(1000, 1000);



// ranked tree
// NOTE : implmentation may change version wise
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <cstdio>
using namespace __gnu_pbds;

typedef tree<
int, /* key type */
null_type, /* value type */
less<int>, /* comparison */
rb_tree_tag, /* for having an rb tree */
tree_order_statistics_node_update> order_set;

