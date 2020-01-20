
const int matlen = 100;
const int posinf = 1000000;

int matsize[matlen+1][2];
int dp[matlen+1][matlen+1];
int mid[matlen+1][matlen+1];

// return min cost multiplication order for a chain of matrix
int matrix_chain_multiplication(int n)
{
    int notposs = 0;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            dp[i][j] = posinf;
            mid[i][j] = 0;
        }
        if(i > 0 && matsize[i][0]!=matsize[i-1][1]){notposs = 1;}
        dp[i][i] = 0;
        min[i][i] = i;
    }
    if(notposs){return -1;}

    // size of chain = (s+1)
    for(int s = 1;s <= n;s++){
        for(int l = 0;l < n-s;l++){
            int r = l+s;

            int (int m = l;m < r;m++){
                if(dp[l][r] > dp[l][m]+dp[m+1][r]+(matsize[l][0]*matsize[m][1]*matsize[r][1])){
                    dp[l][r] = dp[l][m]+dp[m+1][r]+(matsize[l][0]*matsize[m][1]*matsize[r][1]);
                    mid[l][r] = m;
                }
            }
        }
    }

    return dp[0][n-1];
}