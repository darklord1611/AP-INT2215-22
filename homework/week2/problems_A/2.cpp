#include <iostream>

using namespace std;

int main()
{
    int k;
    cin >> k;
    while(k >= 3) 
    {
        k /= 3;
    }
    cout << k;
    return 0;
}
