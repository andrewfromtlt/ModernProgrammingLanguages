#include <iostream>

using namespace std;

int main() {
    int k;
    int power(int, int);
    for(int i = 0; i < 10; i++) {
        k = power(2, i);
        cout << "i = " << i << ", k = " << k << endl;
    }

    return 0;
}

int power(int x, int n) {
    int p = 1;
    for(int i = 1; i <= n; i++) p *= x;
    return p;
}
