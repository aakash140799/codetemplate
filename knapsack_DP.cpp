
const int itemlen = 100;
const int itemsize = 100;
const int posinf = 1000000;

int itemcost[itemlen+1];
int itemsize[itemlen+1];
int dp[itemlen+1][itemsize+1];


// knapsack problem to select items within maxsize, to maximize cost of items
int knapsack(int n,int maxsize)
{
    for(int i = 0;i <= n+1;i++){
        for(int j = 0;j <= maxsize;j++){
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;
    // ith item not added yet
    for(int i = 0;i <= n;i++){
        for(int j = 0;j <= maxsize;j++){
            if(dp[i][j] == -1){continue;}

            // without adding ith item
            if(dp[i+1][j] < dp[i][j]){
                dp[i+1][j] = dp[i][j];
            }

            // with adding ith item
            int nsze = j+itemsize[i];
            int nc = dp[i][j] + itemcost[i];
            if(nsze <= maxsize && dp[i+1][nsze] < nc){
                dp[i+1][nsze] = nc;
            }
        }
    }

    int c = 0;
    for(int i = 0;i <= maxsize;i++){
        if(dp[n+1][i] != -1 && dp[n+1][i] > c){
            c = dp[n+1][i];
        }
    }

    return c;
}