#include <iostream>
#include<cmath>

using namespace std;

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n;i++) 
    {
        for(int j = -(n - 1); j <= n - 1;j++) 
        {
            char c = (abs(i) >= abs(j)) ? '*' : ' ';
            cout << c;
        }
        cout << endl;
    }
    return 0;
}
