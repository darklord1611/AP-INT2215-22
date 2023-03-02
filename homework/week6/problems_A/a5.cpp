#include <iostream>

using namespace std;

long F(int n) { 
   if (n == 0) return 0; 
   if (n == 1) return 1; 
   return F(n-1) + F(n-2); 
}

long F2(int n) 
{
    int f[n + 1];
    f[0] = 0;
    f[1] = 1;
    for(int i = 2; i <= n;i++) 
    {
        f[i] = f[i - 2] + f[i - 1];
    }
    return f[n];
}
int main()
{
    // cout << F(60);  runtime exceed
    cout << F2(60);
    return 0;
}
