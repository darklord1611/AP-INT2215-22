#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    while(true) 
    {
        int N;
        cin >> N;
        if(N == -1) 
        {
            cout << "Bye";
            break;
        }
        if(N >= 0 && N % 5 == 0) 
        {
            cout << N / 5 << endl;
        } else cout << -1 << endl;
    }
    return 0;
}
