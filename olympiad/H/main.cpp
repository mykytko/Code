#include <iostream>
#include <unordered_map>

using namespace std;

int N;
string *str;
unordered_map<string, int> map;

bool check(string name)
{
    int number = map.find(name)->second;
    int totalNumber = 0;
    for (pair<string, int> p : map)
    {
        if (p.first == name)
        {
            continue;
        }

        totalNumber += p.second;
    }
    if (number - 1 > totalNumber) return true;
    return false;
}

int main(int, char**) {
    cin >> N;
    str = new string[N];
    
    for (int i = 0; i < N; i++)
    {
        cin >> str[i];
    }

    int counter = 0;
    int number;
    for (int i = 0; i < N; i++)
    {
        if (map.count(str[i]))
        {
            number = map.find(str[i])->second;
            number++;
            map.erase(str[i]);
            map.insert(pair<string, int>(str[i], number));
            if (check(str[i]))
            {
                counter++;
            }
        }
        else
        {
            map.insert(pair<string, int>(str[i], 1));
        }
    }

    cout << counter << endl;
    delete[] str;
}
