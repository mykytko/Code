#include <iostream>
#include <algorithm>

using namespace std;

struct Rect
{
    int coords[6];
    int ori;
};

int main(int, char **)
{
    int N;
    cin >> N;
    Rect *rects = new Rect[N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cin >> rects[i].coords[j];
        }
        for (int j = 0; j < 3; j++)
        {
            if (rects[i].coords[j] == rects[i].coords[j + 3])
            {
                rects[i].ori = j;
            }
            else if (rects[i].coords[j] > rects[i].coords[j + 3])
            {
                swap(rects[i].coords[j], rects[i].coords[j + 3]);
            }
        }
    }

    int counter = 0;

    int bufcoords[4];
    int found = 0;
    int ori;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            ori = rects[j].ori;
            if ((rects[i].coords[ori] <= rects[j].coords[ori + 3]) &&
                    (rects[i].coords[ori] >= rects[j].coords[ori]))
            {
                found = 0;
                for (int k = 0; k < 2; k++)
                {
                    if (ori == k)
                    {
                        found++;
                    }
                    bufcoords[k] = max(rects[i].coords[k + found], rects[j].coords[k + found]);
                    bufcoords[k + 2] = min(rects[i].coords[k + 3 + found], rects[j].coords[k + 3 + found]);
                }
                if ((bufcoords[0] <= bufcoords[2]) && (bufcoords[1] <= bufcoords[3]))
                {
                    counter++;
                }
            }
        }
    }

    cout << counter << endl;

    delete[] rects;
}
