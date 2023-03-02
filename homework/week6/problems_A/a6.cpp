#include <iostream>
using namespace std;

void check(int n) 
{
    int arr[100000];
    if(n == 0) return;
    return check(n - 1);
}

int main() {
    check(19); // work fine
    check(20); // out of memory
    return 0;
}
// 