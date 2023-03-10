#include<iostream>

using namespace std;

struct Point 
{
    int x;
    int y;
    Point(int _x, int _y) 
    {
        x = _x;
        y = _y;
    }
};
void print1(Point a) 
    {
        cout << "(" << a.x << ", " << a.y << ")" << endl;
    }

void print2(Point &a) 
{
    cout << cout << "(" << a.x << ", " << a.y << ")" << endl;
}

int main() 
{
    Point p(3,5);
    print(p);
    return 0;
}