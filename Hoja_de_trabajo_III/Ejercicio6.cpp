#include <iostream>
using namespace std;

int main () {

    int n;

    cout << "Ingrese un numero entero: ";
    cin >> n;

    int i = 1;

    while (i <= n)
    {
        int espacios = n - i;
        int r = 1;

        while (r <= espacios)
        {
            cout << " ";
            r++;
        }

        int l = 1;

        while (l <= (2 * i -1))
        {
            cout << "*";
            l++;
        }
        
        cout << endl;
        i++;
    }

    cout << "\nEstudiante: Jose Daniel Real Garcia" << endl << "Carnet: 9941-25-837";

    return 0;
}