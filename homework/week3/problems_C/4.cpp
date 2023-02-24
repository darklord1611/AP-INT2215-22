#include <iostream>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    char mine[m][n];
    for(int i = 0; i < m;i++) 
    {
        for(int j = 0; j < n;j++) 
        {
            cin >> mine[i][j];
        }
    }
    for(int i = 0; i < m;i++) 
    {
        for(int j = 0; j < n;j++) 
        {
            if(mine[i][j] == '*') continue;
            int cnt = 0;
            for(int k = i - 1; k <= i + 1;k++) 
            {
                if(k >= 0 && k <= m - 1) 
                {
                    for(int l = j - 1; l <= j + 1;l++) 
                    {
                        if(l >= 0 && l <= n - 1) 
                        {
                            if(mine[k][l] == '*') cnt++;
                        }
                    }
                }
            }
            mine[i][j] = char(cnt + 48);
        }
    }
    for(int i = 0; i < m;i++) 
    {
        for(int j = 0; j < n;j++) 
        {
            cout << mine[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
