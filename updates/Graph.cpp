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





// ALways check vis[counter] before using dep, par values
// there may be two weights for u,v in question
// bfs(src, edges, onStart, reset)
// bfsForest(n, edges, onStart, reset)
// dfs(src, edges, onStart, onEnd, reset)
// dfsForest(n, edges, onStart, onEnd)
// relaxPath(n, edges, weights, setNegInf)
// bellman(src, n, edges, weights, runTwice, reset)
// dijkstra(src, n, edges, weights)
// dijkstra(src, n, edges, weights(int,int))
//, dfs, runBfsAll, runDfsAll, findShortestPathNegWeights, dijkstra
struct Graph{ 
    static const int size = 3e5;
    const int64_t posInf = 1e18;
    const int64_t negInf =-1e18;

    Graph(int sizeArg) {
        assert(sizeArg < size);
    }

    int vis[size];
    int dep[size];
    int par[size];
    int counter = 1;

    stack<int> stk;
    queue<int> que;

    // TESTED
    void bfs(int src, list<int> edges[size], void onStart(int x, int p, int d), bool reset) {
        // reset
        if(reset){counter++;}

        // push
        que.push(src);
        vis[src] = counter;
        dep[src] = 0;
        par[src] = 0;

        // iterate
        while(que.size()) {
            int top = que.front();
            que.pop();

            onStart(top, par[top], dep[top]);

            for(int child : edges[top]) {
                if(vis[child] < counter) {
                    que.push(child);
                    vis[child] = counter;
                    dep[child] = dep[top] + 1;
                    par[child] = top;
                }
            }
        }
    }

    // TESTED
    void BfsForest(int n, list<int> edges[size], void onStart(int x, int p, int d)) {
        // reset
        counter++;

        // iterate
        for(int i = 1; i <= n; i++) {
            if(vis[i] < counter){
                bfs(i, edges, onStart, false);
            }
        }
    }

    // TESTED
    int visCnt[size];
    void dfs(int src, list<int> edges[size], void onStart(int x, int p, int d), void onEnd(int x, int p, int d), bool reset) {
        // reset
        if(reset){counter++;}

        // push
        stk.push(src);
        vis[src] = counter;
        dep[src] = 0;
        par[src] = 0;
        visCnt[src] = 0;

        // iterate
        while(stk.size()) {
            int top = stk.top();

            if(vis[top] == counter) { // exploring

                if(visCnt[top] == 0){
                    onStart(top, par[top], dep[top]);
                }

                if(visCnt[top] == edges[top].size()) {
                    vis[top] = counter+1;
                    continue;
                }

                int child = edges[top].front();
                edges[top].pop_front();
                edges[top].push_back(child);

                if(vis[child] < counter) {
                    stk.push(child);
                    vis[child] = counter;
                    dep[child] = dep[top] + 1;
                    par[child] = top;
                    visCnt[child] = 0;
                }

                visCnt[top]++;

            } else { // explored
                onEnd(top, par[top], dep[top]);
                stk.pop();
            }
        }
    }

    // TESTED
    void dfsForest(int n, list<int> edges[size], void onStart(int x, int p, int d), void onEnd(int x, int p, int d)) {
        // reset
        counter++;

        // iterate
        for(int i = 1; i <= n; i++) {
            if(vis[i] < counter){
                dfs(i, edges, onStart, onEnd, false);
            }
        }
    }

    int64_t dis[size];
    // tested
    int relaxPaths(int n, list<int> edges[size], list<int64_t> weights[size], bool setNegIng) {

        int x = 0;
        for(int u = 1; u <= n; u++) {
            list<int64_t>::iterator w = weights[u].begin();

            for(int v : edges[u]) {
                if(dis[u] == negInf && setNegIng){
                    dis[v] = negInf;
                    par[v] = u;
                    x = v;

                    w++;continue;
                }
                if(dis[u] == posInf){w++;continue;}

                if(dis[v] > dis[u] + *w) {
                    dis[v] = setNegIng ? negInf : dis[u] + *w;
                    par[v] = u;
                    x = v;

                    w++;continue;
                }
            }
        }

        return x;
    }


    // TESTED
    int bellman(int src, int n, list<int> edges[size], list<int64_t> weights[size], bool runTwice, bool reset) {
        
        // reset
        if(reset){
            counter++;
            fill(dis, dis+n+1, posInf);
        }

        // push
        dis[src] = 0;
        par[src] = 0;

        // iterate
        for(int i = 1; i <= n; i++) {
            relaxPaths(n, edges, weights, false);
        }

        int x = relaxPaths(n, edges, weights, false);

        
        // iterate
        if(runTwice) {
            for(int i = 1; i <= n; i++) {
                x = relaxPaths(n, edges, weights, true);
            }
        }

        return x;
    }



    struct disV{int64_t v; int64_t d;
    bool operator<(const disV &arg) const{
            return make_pair(d, v) < make_pair(arg.d, arg.v);}};

    // TESTED
    void dijkstra(int src, int n, list<int> edges[size], list<int64_t> weights[size]) {
        
        // reset
        counter++;
        fill(dis, dis+n+1, 1e18);
        static set<disV> heap;
        heap.clear();
 
        // push
        dis[src] = 0;
        par[src] = 0;
        heap.insert(disV{src, 0});
 
        // iterate
        while(heap.size()) {
 
            disV top = *(heap.begin());
            heap.erase(top);
 
            vis[top.v] = counter;
 
            list<int64_t>::iterator w = weights[top.v].begin();
            for(int child : edges[top.v]) {
                if(vis[child] == counter){w++; continue;}
 
                // remove child from heap
                heap.erase(disV{child, dis[child]});
                
                // check dis
                if(dis[child] > dis[top.v] + *w){
                    dis[child] = dis[top.v] + *w;
                    par[child] = top.v;
                }
 
                // insert back child
                heap.insert(disV{child, dis[child]});
 
                w++;
            }
        }
    }

    void dijkstra(int src, int n, list<int> edges[size], int64_t weights(int, int)) {
        
        // reset
        counter++;
        fill(dis, dis+n+1, 1e18);
        static set<disV> heap;
        heap.clear();
 
        // push
        dis[src] = 0;
        par[src] = 0;
        heap.insert(disV{src, 0});
 
        // iterate
        while(heap.size()) {
 
            disV top = *(heap.begin());
            heap.erase(top);
 
            vis[top.v] = counter;
 
            for(int child : edges[top.v]) {
                if(vis[child] == counter){continue;}
 
                // remove child from heap
                heap.erase(disV{child, dis[child]});
                
                // check dis
                if(dis[child] > dis[top.v] + weights(top.v, child)){
                    dis[child] = dis[top.v] + weights(top.v, child);
                    par[child] = top.v;
                }
 
                // insert back child
                heap.insert(disV{child, dis[child]});
 
            }
        }
    }
};
Graph gh(2e5);






const int row = 1002;
const int col = 1002;

struct Cell{int i, j;
    operator int() const {
        return (i * col)  + j;
    }

    bool before(int i1, int j1) {
        return i <= i1 && j <= j1;
    }

    bool after(int i1, int j1) {
        return i >= i1 && j >= j1;
    }
};


// bfs(src, isEdge(p, x, c), onStart(x, p, d), reset)
// bfs(n, m, isEdge(p, x, c), onStart(x, p, d))
// bfs(n, m, isRoot(x), isEdges(p, x, c), onStart(x, p, d))
struct DenseGraph{
    
    DenseGraph(int rowArg, int colArg) {
        assert(row == rowArg);
        assert(col == colArg);
    }


    int vis[row * col];
    int dep[row * col];
    Cell par[row * col];
    int counter = 1;


    queue<Cell> que;

    void bfs(Cell src, bool isEdge(Cell p, Cell x, Cell c), void onStart(Cell x, Cell p, int d), bool reset){
        // reset
        if(reset){counter++;}

        // push
        que.push(src);
        vis[src] = counter;
        dep[src] = 0;
        par[src] = Cell{0,0};
        

        // iterate
        while(que.size()) {
            Cell top = que.front();
            que.pop();

            onStart(top, par[top], dep[top]);
            
            for(int d = -1; d <= 1; d += 2){

                Cell c1 = Cell{top.i+d, top.j};
                if(vis[c1] < counter && isEdge(par[top], top, c1)) {
                        
                    que.push(c1);
                    vis[c1] = counter;
                    dep[c1] = dep[top] + 1;
                    par[c1] = top;
                }

                c1 = Cell{top.i, top.j+d};
                if(vis[c1] < counter && isEdge(par[top], top, c1)) {
                        
                    que.push(c1);
                    vis[c1] = counter;
                    dep[c1] = dep[top] + 1;
                    par[c1] = top;
                }
            }
        }
    }


    void bfs(int n, int m, bool isEdge(Cell p, Cell x, Cell c), void onStart(Cell x, Cell p, int d)) {
        // reset
        counter++;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                
                if(vis[Cell{i,j}] < counter && isEdge(Cell{0,0}, Cell{0,0}, Cell{i,j})) {
                    bfs(Cell{i,j}, isEdge, onStart, false);
                }
            }
        }
    }


    // TESTED
    void bfs(int n, int m, bool isRoot(Cell x), bool isEdge(Cell p, Cell x, Cell c), void onStart(Cell x, Cell p, int d)) {
        // reset
        counter++;

        // push
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(isRoot(Cell{i,j})){
                    que.push(Cell{i,j});
                    vis[Cell{i,j}] = counter;
                    dep[Cell{i,j}] = 0;
                    par[Cell{i,j}] = Cell{0,0};
                }
            }
        }


        // iterate
        while(que.size()) {
            Cell top = que.front();
            que.pop();

            onStart(top, par[top], dep[top]);
            
            for(int d = -1; d <= 1; d += 2){

                Cell c1 = Cell{top.i+d, top.j};
                if(vis[c1] < counter && isEdge(par[top], top, c1)) {
                        
                    que.push(c1);
                    vis[c1] = counter;
                    dep[c1] = dep[top] + 1;
                    par[c1] = top;
                }

                c1 = Cell{top.i, top.j+d};
                if(vis[c1] < counter && isEdge(par[top], top, c1)) {
                        
                    que.push(c1);
                    vis[c1] = counter;
                    dep[c1] = dep[top] + 1;
                    par[c1] = top;
                }
            }
        }
    }
};
DenseGraph dg(row, col);
