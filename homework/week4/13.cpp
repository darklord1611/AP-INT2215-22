#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T--) 
    {
        int n;
        bool exist = false;
        cin >> n;
        int arr[n], sum[n];
        for(int i = 0; i < n;i++) cin >> arr[i];
        sum[0] = arr[0];
        for(int i = 1; i < n;i++) 
        {
            sum[i] = sum[i - 1] + arr[i];
        }
        for(int i = 0; i <= n - 1;i++) 
        {
            int previousSum = sum[i] - arr[i];
            int followingSum = sum[n - 1] - sum[i];
            if((i == 0 && followingSum == 0) || (i == n - 1 && previousSum == 0)) 
            {
                exist = true;
                break;
            }
            if(previousSum == followingSum) 
            {
                exist = true;
                break;
            }
        }
        if(exist) 
        {
            cout << "YES" << endl;
        } else cout << "NO" << endl;
    }
    return 0;
}
