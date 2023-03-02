#include <iostream>

using namespace std;

void print(int arr[]) 
{
    cout << &arr << " " << &arr[0] << endl;
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n;i++) cin >> arr[i];
    cout << &arr << " " << &arr[0] << endl;
    print(arr);
    return 0;
}
// mảng được truyền vào hàm theo tham trị tr(pass by value), địa chỉ đầu tiên của mảng trong hàm trỏ đến địa chỉ của phần tử đầu tiên của mảng ban đầu.đầu

