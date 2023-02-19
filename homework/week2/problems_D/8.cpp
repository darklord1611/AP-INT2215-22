#include <iostream>
#include <cmath>

using namespace std;

// a*x^2 + b*x + c = 0
int main()
{
    int a,b,c;
    double x1, x2;
    cin >> a >> b >> c;
    int delta = b*b - 4*a*c;
    if(delta > 0) 
    {
        x1 = (-b - sqrt(delta))/(2*a);
        x2 = -b/a - x1;
        cout << x1 << " " << x2;
    } else if(delta == 0) 
    {
        x1 = -b/(2*a);
        cout << x1;
    } else 
    {
        double realPart = -b/(2*a);
        double imaginaryPart = delta / (4*a*a);
        cout << realPart << " " << imaginaryPart << endl;
        cout << realPart << " " << -1 * imaginaryPart;
    }
    return 0;
}
