#include <iostream>
using namespace std;

// a1*x + b1*y = c1
// a2*x + b2*y = c2

int main()
{
    int a1,a2,b1,b2,c1,c2;
    cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
    int determinant = a1*b2 - a2*b1;
    if(determinant == 0) 
    {
        if(c1 == c2)
            {
                cout << "Vo so nghiem";
            }
        else cout << "Vo nghiem";
    }
    else 
    {
        double x = (double) (b2*c1 - b1*c2) / determinant;
        double y = (double) (a1*c2 - a2*c1) / determinant;
        cout << x << " " << y;
    }
    return 0;
}