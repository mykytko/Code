#include <iostream>

using namespace std;

void recur(string str)
{
    if (str.length() == 0)
    {
        return;
    }
    recur(str.substr(1));
    cout << str[0];
}

int main(int, char**) {
    string str;
    cout << "Введіть рядок: ";
    getline(cin, str);

    cout << "Ітераційний метод: ";
    for (int i = str.length() - 1; i >= 0; i--)
    {
        cout << str[i];
    }
    cout << endl;
    cout << "Рекурсивний метод: ";
    recur(str);
    cout << endl;
}
