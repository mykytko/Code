#include <iostream>

using namespace std;

void swapInts(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

void swapPointers(int *&a, int *&b)
{
    int *c = a;
    a = b;
    b = c;
}

int find_min(int *arr, int j, int N)
{
    int min = j;
    for (int i = j + 1; i < N; i++)
    {
        if (arr[i] < arr[min])
        {
            min = i;
            if (arr[min] == 0)
            {
                break;
            }
        }
    }
    return min;
}

int main(int, char**) {
    int N;
    cout << "Введіть розмірність матриці N:\n";
    cin >> N;
    cout << "Введіть матрицю:\n";
    // виділення пам'яті та введення матриці
    int *data = new int[N]; // кількість нульових елементів кожного рядка
    for (int i = 0; i < N; i++)
    {
        data[i] = 0;
    }
    int **matrix = new int *[N]; // сама матриця
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new int[N];
        for (int j = 0; j < N; j++)
        {
            cin >> matrix[i][j];
            if (matrix[i][j] == 0)
            {
                data[i]++;
            }
        }
    }

    // сортування алгоритмом selection sort
    for (int i = 0; i < N; i++)
    {
        int min = find_min(data, i, N);
        swapInts(data[i], data[min]);
        swapPointers(matrix[i], matrix[min]);
    }

    cout << "Вихідна матриця:\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // звільнити пам'ять
    for (int i = 0; i < N; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}
