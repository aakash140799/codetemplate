#include <iostream>
#include <queue>
#include <set>
#include <list>
#include <stack>
#include <algorithm>
#include <cassert>
#include <cmath>
using namespace std;

// bfs(src, edges, onStart(x, p, d))
// dfs(src, edges, onStart(x, p, d))
// dfs(src, edges, onStart(x, p, d), onEnd(x, p, d))
// dfsEvery(src, edges, onEvery(x, p, c, d))
// leafUp(n, edges, action(x, p))
struct Tree { // bfs, dfs, dfsEvery, leafUP

    const static int size = 4e5;

    int dep[size];
    int vis[size];
    int par[size];

    queue<int> que;
    stack<int> stk;

    int counter = 1;

    Tree(int sizeArg) {
        assert(size > sizeArg);
    }
    
    void bfs(int src, list<int> edges[size], void onStart(int x, int p, int d))
    {
        // reset
        counter++;
        while(que.size()){que.pop();}
        
        // push
        que.push(src);
        vis[src] = counter;
        dep[src] = 0;
        par[src] = 0;

        // iterate
        while(que.size())
        {
            int top = que.front();
            que.pop();

            onStart(top, par[top], dep[top]);

            for(int child : edges[top]){
                if(vis[child] != counter) {
                    que.push(child);
                    vis[child] = counter;
                    dep[child] = dep[top]+1;
                    par[child] = top;
                }
            }
        }
    }

    // TESTED
    void dfs(int src, list<int> edges[size], void onStart(int x, int p, int d))
    {
        // reset
        counter++;
        while(stk.size()){stk.pop();}

        // push
        stk.push(src);
        vis[src] = counter;
        dep[src] = 0;
        par[src] = 0;

        // iterate
        while(stk.size())
        {
            int top = stk.top();
            stk.pop();

            onStart(top, par[top], dep[top]);

            for(int child : edges[top]){
                if(vis[child] != counter) {
                    stk.push(child);
                    vis[child] = counter;
                    dep[child] = dep[top] + 1;
                    par[child] = top;
                }
            }
        }
    }

    // TESTED
    void dfs(int src, list<int> edges[size], void onStart(int x, int p, int d), void onEnd(int x, int p, int d))
    {
        // reset
        counter++;
        while(stk.size()){stk.pop();}

        // push
        stk.push(src);
        vis[src] = counter;
        dep[src] = 0;
        par[src] = 0;

        // iterate
        while(stk.size())
        {
            int top = stk.top();

            // first visit
            if(vis[top] == counter) {

                onStart(top, par[top], dep[top]);
                for(int child : edges[top]){
                    if(vis[child] < counter) {
                        stk.push(child);
                        vis[child] = counter;
                        dep[child] = dep[top]+1;
                        par[child] = top;
                    }
                }

                vis[top] = counter+1;
            }
            // last visit
            else{
                onEnd(top, par[top], dep[top]);
                stk.pop();
            }            
        }

        // return
        counter++;
    }

    int visTime[size];
    // TESTED
    void dfsEvery(int src, list<int> edges[size], void onEvery(int x, int p, int c, int d)) {
        
        // reset
        counter++;

        // push
        stk.push(src);
        vis[src] = counter;
        dep[src] = 0;
        par[src] = 0;
        visTime[src] = 0;

        while(stk.size())
        {
            int top = stk.top();
            
            // if not fully explored
            if(vis[top] == counter) {

                if(visTime[top] == edges[top].size()){
                    vis[top] = counter+1;
                    continue;
                }

                int child = edges[top].front();
                edges[top].pop_front();
                edges[top].push_back(child);

                if(vis[child] < counter){
                    stk.push(child);
                    vis[child] = counter;
                    dep[child] = dep[top]+1;
                    par[child] = top;

                    onEvery(top, par[top], child, dep[top]);
                }

                visTime[top]++;
            } else{
                // fully visited
                onEvery(top, par[top], 0, dep[top]);
                stk.pop();
            }
        }

        // return
        counter += 2;
    }


    int deg[size];
    struct degV{int d, v; 
        bool operator<(const degV &arg) const {return make_pair(d,v) < make_pair(arg.d,arg.v);}};
    set<degV> nodes;    
    
    // TESTED
    // Don't ends at center
    void leafUp(int n, list<int> edges[size], void action(int x, int p))
    {
        // reset
        counter++;
        nodes.clear();
        
        // push
        for(int i = 1; i <= n; i++){deg[i] = edges[i].size();}
        for(int i = 1; i <= n; i++){nodes.insert({deg[i], i});}

        // iterate
        while(nodes.size()) {
            degV top = *(nodes.begin());
            nodes.erase(nodes.begin());
            
            par[top.v] = 0;
            vis[top.v] = counter;
            for(int child : edges[top.v]) {
                if(vis[child] < counter) {
                    par[top.v] = child;
                    break;
                }
            }

            if(par[top.v] != 0){
                degV ptop = *(nodes.lower_bound({deg[par[top.v]], par[top.v]}));
                nodes.erase(nodes.lower_bound({deg[par[top.v]], par[top.v]}));
                

                deg[ptop.v]--;
                ptop.d--;
                top.d--;
                nodes.insert(ptop);
            }

            action(top.v, par[top.v]);
        }
    }
};
Tree tree(2e5);


// make_lca(n, edges)
// query(a, b)
// needs SegTree
namespace Lca {

    static const int size = 2e5;

    void lca(int sizeArg) {
        assert(sizeArg < size);
    }


    int euler[size * 2];
    int indexOf[size];
    int counter = 1;

    Tree tree = Tree(size);
    SegTree<int> seg = SegTree<int>(size * 2, 0);

    void onEvery(int x, int p, int c, int d) {
        euler[counter++] = c;
        if(indexOf[x]==0){indexOf[x]=counter-1;}
    }

    int makeFunc(int i) {
        return i < counter ? euler[i] : 0;
    }

    int merge(int i1, int i2) {
        return tree.dep[i1] < tree.dep[i2] ? i1 : i2;
    }

    void make_lca(int n, list<int> edges[size]) {
        
        // reset
        fill(indexOf, indexOf+n+1, 0);
        counter = 1;

        tree.dep[0] = 2e7;
        tree.dfsEvery(1, edges, onEvery);
        seg.make_seg(counter-1, makeFunc, merge);
    }

    int query(int a, int b) {
        return seg.query(merge, min(indexOf[a], indexOf[b]), max(indexOf[a], indexOf[b]));
    }
};
Lca.lca(2e5);
