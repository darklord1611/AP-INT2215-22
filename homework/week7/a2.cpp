#include <iostream>

using namespace std;

void print(int arr[]) 
{
    cout << sizeof(arr) << endl;
}

int main()
{
    int arr[5];
    cout << sizeof(arr) << endl;
    print(arr);
    return 0;
}
