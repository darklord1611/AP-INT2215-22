#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double Celsius(double F) 
{
    double C = (F - 32)*5/9;
    return C;
}
double Kelvin(double C) 
{
    return C + 273.15;
}

int main()
{
    double min, max;
    int step_size;
    cin >> min >> max >> step_size;
    cout << "Farhrenheit    Celsius       Kelvin" << endl;
    cout << endl;
    cout << endl;
    for(double i = min; i <= max;i += step_size) 
    {
        cout << i << "           " << Celsius(i) << "            " << Kelvin(Celsius(i)) << endl;
    }
    return 0;
}
