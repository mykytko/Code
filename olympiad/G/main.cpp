#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int sizeX, sizeY;
bool ****visited;
class cfg;

struct cds
{
    cfg *p;
    int x, y;
    bool ind;

    cds()
    {
        p = nullptr;
        x = -1;
        y = -1;
        ind = -1;
    }

    cds(cfg *parent, int xa, int ya)
    {
        p = parent;
        x = xa;
        y = ya;
    }

    bool left();
    bool right();
    bool up();
    bool down();
};

class cfg
{
public:
    cds *pr[2];

    cfg()
    {
        pr[0] = new cds();
        pr[1] = new cds();
        pr[0]->p = this;
        pr[1]->p = this;
        pr[0]->ind = 0;
        pr[1]->ind = 0;
    }

    cfg(int x1, int y1, int x2, int y2)
    {
        pr[0] = new cds(this, x1, y1);
        pr[1] = new cds(this, x2, y2);
        pr[0]->ind = 0;
        pr[1]->ind = 1;
    }
};

cfg cur;

bool isVisited(cfg *conf, int x, int y, bool index)
{
    if ((x < 0) || (x >= sizeX) || (y < 0) || (y >= sizeY) ||
        ((conf->pr[index]->x == conf->pr[!index]->x) && (conf->pr[index]->y == conf->pr[!index]->y)))
    {
        return true;
    }
    if ((int)index == 0)
    {
        return visited[x][y][conf->pr[1]->x][conf->pr[1]->y];
    }
    else
    {
        return visited[conf->pr[0]->x][conf->pr[0]->y][x][y];
    }
}

void makeVisited(cfg *conf, int x, int y, bool index)
{
    if ((int)index == 0)
    {
        visited[x][y][conf->pr[1]->x][conf->pr[1]->y] = true;
    }
    else
    {
        visited[conf->pr[0]->x][conf->pr[0]->y][x][y] = true;
    }
}

bool cds::left()
{
    if (isVisited(p, x - 1, y, ind))
    {
        return false;
    }
    while (!isVisited(p, x - 1, y, ind))
    {
        x--;
    }
    makeVisited(p, x, y, ind);
    return true;
}

bool cds::right()
{
    if (isVisited(p, x + 1, y, ind))
    {
        return false;
    }
    while (!isVisited(p, x + 1, y, ind))
    {
        x++;
    }
    return true;
}

bool cds::up()
{
    if (isVisited(p, x, y - 1, ind))
    {
        return false;
    }
    while (!isVisited(p, x, y - 1, ind))
    {
        y--;
    }
    return true;
}

bool cds::down()
{
    if (isVisited(p, x, y + 1, ind))
    {
        return false;
    }
    while (!isVisited(p, x, y + 1, ind))
    {
        y++;
    }
    return true;
}

bool destinationIsReached(cfg &desired)
{
    int hey = 0;
    if (desired.pr[hey]->x == -1)
    {
        hey++;
    }
    return ((cur.pr[hey]->x == desired.pr[hey]->x) && (cur.pr[hey]->y == desired.pr[hey]->y));
}

void check(queue<cfg> &q, int who, int op)
{
    cfg newCfg = cur;
    switch (op)
    {
    case 0:
        if (newCfg.pr[who]->left())
        {
            q.push(newCfg);
            visited[newCfg.pr[0]->x][newCfg.pr[0]->y][newCfg.pr[1]->x][newCfg.pr[1]->y] = true;
        }
        break;
    case 1:
        if (newCfg.pr[who]->up())
        {
            q.push(newCfg);
            visited[newCfg.pr[0]->x][newCfg.pr[0]->y][newCfg.pr[1]->x][newCfg.pr[1]->y] = true;
        }
        break;
    case 2:
        if (newCfg.pr[who]->right())
        {
            q.push(newCfg);
            visited[newCfg.pr[0]->x][newCfg.pr[0]->y][newCfg.pr[1]->x][newCfg.pr[1]->y] = true;
        }
        break;
    case 3:
        if (newCfg.pr[who]->down())
        {
            q.push(newCfg);
            visited[newCfg.pr[0]->x][newCfg.pr[0]->y][newCfg.pr[1]->x][newCfg.pr[1]->y] = true;
        }
        break;
    }
}

int main(int, char **)
{
    cur = cfg();
    cin >> sizeX;
    cin >> sizeY;
    char **matrix = new char *[sizeY];
    for (int i = 0; i < sizeX; i++)
    {
        matrix[i] = new char[sizeX];
    }
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            cin >> matrix[i][j];
        }
    }

    visited = new bool ***[sizeX];
    for (int i = 0; i < sizeX; i++)
    {
        visited[i] = new bool **[sizeY];
        for (int j = 0; j < sizeY; j++)
        {
            visited[i][j] = new bool *[sizeX];
            for (int k = 0; k < sizeX; k++)
            {
                visited[i][j][k] = new bool[sizeY];
            }
        }
    }

    queue<cfg> q;
    int x1, y1, x2, y2;
    cfg desiredCfg(-1, -1, -1, -1);

    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            switch (matrix[i][j])
            {
            case 'P':
                x1 = j;
                y1 = i;
                break;
            case 'R':
                x2 = j;
                y2 = i;
                break;
            case '#':
                for (int k = 0; k < sizeY; k++)
                {
                    for (int l = 0; l < sizeY; l++)
                    {
                        visited[j][i][l][k] = true;
                        visited[l][k][j][i] = true;
                    }
                }
                break;
            case '<':
                desiredCfg.pr[0]->x = j;
                desiredCfg.pr[0]->y = i;
                break;
            case '>':
                desiredCfg.pr[1]->x = j;
                desiredCfg.pr[1]->y = i;
                break;
            case '.':
                break;
            default:
                cout << "Invalid map." << endl;
                return 0;
            }
        }
    }

    if (((desiredCfg.pr[0]->x == -1) && (desiredCfg.pr[0]->y == -1) && ((desiredCfg.pr[1]->x == -1) || (desiredCfg.pr[1]->y == -1))) ||
        ((((desiredCfg.pr[0]->x == -1) || (desiredCfg.pr[0]->y == -1)) && (desiredCfg.pr[1]->x == -1) && (desiredCfg.pr[1]->y == -1))))
    {
        cout << "Invalid map." << endl;
    }

    q.push(cfg(x1, y1, x2, y2));
    cur = q.front();
    bool dest = destinationIsReached(desiredCfg);
    int counter = 0;
    while (!q.empty())
    {
        counter++;
        cur = q.front();
        dest = destinationIsReached(desiredCfg);
        if (dest)
        {
            break;
        }
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            check(q, 0, i);
            check(q, 1, i);
        }
    }
    if (!dest)
    {
        cout << -1 << endl;
        return -1;
    }
    cout << counter << endl;
}
