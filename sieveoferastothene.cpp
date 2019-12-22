
#include <iostream>
using namespace std;

// bits and prime-values
int bitval[1000001];
int prival[1000001];

int main()
{
    int64_t n = 1000000;
    int l = 0;

    for(int64_t i = 2;i <= n){
        prival[l++] = i;
        int64_t j = i;
        while(i*j <= n){
            bitval[i*j] = 1;
            j++;
        }
        while(++i <= n && bitval[i]){
            i++;
        }
    }
    // all prime-values less than or equal to n
    for(int i = 0;i < l;i++){
        cout << prival[i] << " ";
    }
}
