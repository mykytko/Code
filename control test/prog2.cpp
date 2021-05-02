#include <iostream>

using namespace std;

int main(int, char**) {
    int n, k;
    cout << "Введіть ціле число n > 0: ";
    cin >> n;
    if (n == 1)
    {
        cout << "k = 0\n";
        return 0;
    }
    int number = 1;
    for (k = 1;; k++)
    {
        number *= 2;
        if (n == number)
        {
            break;
        }
    }
    cout << "k = " << k << endl;
    return 0;
}
