#include <iostream>
using namespace std;

int main () {

    int nota = 91;

    if (nota >= 90) {
        cout << "A";
    }

    if (nota >= 80) {
        cout << "B";
    }
    
    if (nota >= 70) {
        cout << "C";
    }
    
    else {
        cout << "Reprobaste";
    }

    return 0;
}