#include <iostream>
#include <vector>

using namespace std;

int n;
long long *numbers;

long long move(long long &u, long long &v)
{
    long long num;
    if (abs(v) < abs(u))
    {
        num = abs(v);
        u += v;
        v = 0;
    }
    else
    {
        num = abs(u);
        v += u;
        u = 0;
    }
    return num;
}

long long findAnswer()
{
    long long answer = 0;
    int iter;
    int i = 0;
    while (i < n)
    {
        while (numbers[i] != 0)
        {
            while (((numbers[i] < 0) == (numbers[i + 1] < 0)) || (numbers[i + 1] == 0))
            {
                numbers[i + 1] += numbers[i];
                answer += abs(numbers[i]);
                numbers[i] = 0;
                i++;
            }
            answer += move(numbers[i], numbers[i + 1]);
        }
        i++;
    }

    return answer;
}

int main(int, char **)
{
    vector<long long> answers;
    cin >> n;
    while (n != 0)
    {
        numbers = new long long[n];
        for (int i = 0; i < n; i++)
        {
            cin >> numbers[i];
        }
        answers.push_back(findAnswer());
        delete[] numbers;
        cin >> n;
    }
    for (int i = 0; i < answers.size(); i++)
    {
        cout << answers[i] << endl;
    }
}
