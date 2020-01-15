
const int vsize = 100;
const int posinf = 1000000;

int edgew[vsize][vsize];

// dp[i][j] = cost of path from ver(0) to all vertices in(binary(i));
int dp[(1<<vsize)][vsize];

int TSP(int n)
{
    for(int i = 0;i < (1<<n);i++){
        for(int j = 0;j < n;j++){
            dp[i][j] = posinf;
        }
    }

    dp[0][0] = 0;
    for(int s = 0;s < (1<<n);s++){
        for(int u = 0;u < n;u++){
            if(dp[s][u] == posinf){continue;}

            for(int v = 0;v < n;v++){
                if(s&(1<<v)){continue;}

                int ns = s|(1<<v);
                int nc = dp[s][u] + mat[u][v];
                if(dp[ns][v] > nc){
                    dp[ns][v] = nc;
                }
            }
        }
    }

    int c = posinf;
    for(int v = 0; v < n;v++){
        if(dp[(1<<n)-1][v] + mat[v][0] < c){
            c = dp[(1<<n)-1][v] + mat[v][0];
        }
    }

    return c;
}