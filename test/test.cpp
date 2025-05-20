#include <iostream>
using namespace std;

void loop_example() {
    int arr[5];
    for (int i = 0; i < 4; ++i)
        arr[i] = arr[i] + 1;
}

int main() {
    loop_example();
    return 0;
}
