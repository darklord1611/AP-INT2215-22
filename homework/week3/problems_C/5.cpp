#include<iostream>
using namespace std;

int main()
{
    int m,n,i = 0, j = 0,k = 0, l = 0, num = 1;
    cin >> m >> n;
    int arr[m][n], res = m*n, end1 = m, end2 = n;
    while(num < res)
        {
            while(j <= n - 1)
                {
                    arr[i][j] = num;
                    num++;
                    if(j == n - 1) {k++; break;}
                    else j++;
                }
            num--;
            while(i <= m - 1)
                {
                    arr[i][j] = num++;
                    if(i == m - 1) {n--; break;}
                    else i++;
                }
            num--;
            while(j >= l)
                {
                    arr[i][j] = num++;
                    if(j == l) {m--; break;}
                    else j--;
                }
            num--;
            while(i >= k)
                {
                    arr[i][j] = num++;
                    if(i == k) {l++; break;}
                    else i--;
                }
            num--;
        }
        for(int i1 = 0; i1 < end1;i1++)
            {
                for(int j1 = 0; j1 < end2;j1++)
                    {
                        cout << arr[i1][j1] << " ";
                    }
                cout << endl;
            }
    return 0;
}
