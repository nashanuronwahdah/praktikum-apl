#include <iostream>
using namespace std;

int faktorialRekursif(int n) {
    if (n <= 1) return 1; // Base case
    return n * faktorialRekursif(n - 1); // Rekursi
}

int main() {
    cout << "5! = " << faktorialRekursif(5) << endl;
    return 0;
}