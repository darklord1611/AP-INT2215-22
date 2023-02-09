#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n;i++) 
    {
        if(i % 2 == 0) cout << i << " ";
    }
    cout << endl;
    
    int cnt = 1;
    while(cnt <= n) 
    {
        if(cnt % 2 == 0) cout << cnt << " ";
        cnt++;
    }
    cout << endl;
    
    cnt = 1;
    do 
    {
        if(cnt % 2 == 0) cout << cnt << " ";
        cnt++;
    } while(cnt <= n);
    return 0;
}
