using System;
using System.Collections.Generic;

namespace Olympiad_1_G
{
    class Program
    {
        static int sizeX, sizeY;
        static bool[,,,] visited;
        static char[,] matrix;

        class Cfg
        {
            private struct Coords
            {
                public int x, y;
                public static bool operator ==(Coords a, Coords b)
                {
                    return (a.x == b.x) && (a.y == b.y);
                }
                public static bool operator !=(Coords a, Coords b)
                {
                    return (a.x != b.x) || (a.y != b.y);
                }
            }
            private Coords[] PR = new Coords[2];
            public int age = 0;
            public Cfg()
            {
                PR[0].x = -1;
                PR[0].y = -1;
                PR[1].x = -1;
                PR[1].y = -1;
            }
            public Cfg(Cfg cfg)
            {
                copyFrom(cfg);
            }
            public void copyFrom(Cfg cfg)
            {
                this.PR[0] = cfg.PR[0];
                this.PR[1] = cfg.PR[1];
                this.age = cfg.age;
            }
            public int getX(int index)
            {
                return PR[index].x;
            }
            public int getY(int index)
            {
                return PR[index].y;
            }
            public void setX(int index, int x)
            {
                PR[index].x = x;
            }
            public void setY(int index, int y)
            {
                PR[index].y = y;
            }
            public bool left(int index)
            {
                int opp = index == 0 ? 1 : 0;
                int originalX = PR[index].x;

                // move as far as possible
                do
                {
                    PR[index].x -= 1;
                } while ((PR[index].x >= 0) && (PR[index] != PR[opp]) && (matrix[PR[index].x, PR[index].y] != '#'));
                PR[index].x += 1;

                // check if there was actual movement
                if (originalX == PR[index].x)
                {
                    PR[index].x = originalX;
                    return false;
                }

                // check if the combination of P and R positions was visited already
                if (visited[PR[0].x, PR[0].y, PR[1].x, PR[1].y])
                {
                    PR[index].x = originalX;
                    return false;
                }

                return true;
            }
            public bool right(int index)
            {
                int opp = index == 0 ? 1 : 0;
                int originalX = PR[index].x;

                // move as far as possible
                do
                {
                    PR[index].x += 1;
                } while ((PR[index].x < sizeX) && (PR[index] != PR[opp]) && (matrix[PR[index].x, PR[index].y] != '#'));
                PR[index].x -= 1;

                // check if there was actual movement
                if (originalX == PR[index].x)
                {
                    PR[index].x = originalX;
                    return false;
                }

                // check if the combination of P and R positions was visited already
                if (visited[PR[0].x, PR[0].y, PR[1].x, PR[1].y])
                {
                    PR[index].x = originalX;
                    return false;
                }

                return true;
            }
            public bool up(int index)
            {
                int opp = index == 0 ? 1 : 0;
                int originalY = PR[index].y;

                // move as far as possible
                do
                {
                    PR[index].y -= 1;
                } while ((PR[index].y >= 0) && (PR[index] != PR[opp]) && (matrix[PR[index].x, PR[index].y] != '#'));
                PR[index].y += 1;

                // check if there was actual movement
                if (originalY == PR[index].y)
                {
                    PR[index].y = originalY;
                    return false;
                }

                // check if the combination of P and R positions was visited already
                if (visited[PR[0].x, PR[0].y, PR[1].x, PR[1].y])
                {
                    PR[index].y = originalY;
                    return false;
                }

                return true;
            }
            public bool down(int index)
            {
                int opp = index == 0 ? 1 : 0;
                int originalY = PR[index].y;

                // move as far as possible
                do
                {
                    PR[index].y += 1;
                } while ((PR[index].y < sizeY) && (PR[index] != PR[opp]) && (matrix[PR[index].x, PR[index].y] != '#'));
                PR[index].y -= 1;

                // check if there was actual movement
                if (originalY == PR[index].y)
                {
                    PR[index].y = originalY;
                    return false;
                }

                // check if the combination of P and R positions was visited already
                if (visited[PR[0].x, PR[0].y, PR[1].x, PR[1].y])
                {
                    PR[index].y = originalY;
                    return false;
                }

                return true;
            }
            public void check(ref Queue<Cfg> q, int index)
            {
                Cfg original = new Cfg(this);
                if (left(index))
                {
                    q.Enqueue(new Cfg(this));
                    visited[PR[0].x, PR[0].y, PR[1].x, PR[1].y] = true;
                    copyFrom(original);
                }
                if (right(index))
                {
                    q.Enqueue(new Cfg(this));
                    visited[PR[0].x, PR[0].y, PR[1].x, PR[1].y] = true;
                    copyFrom(original);
                }
                if (up(index))
                {
                    q.Enqueue(new Cfg(this));
                    visited[PR[0].x, PR[0].y, PR[1].x, PR[1].y] = true;
                    copyFrom(original);
                }
                if (down(index))
                {
                    q.Enqueue(new Cfg(this));
                    visited[PR[0].x, PR[0].y, PR[1].x, PR[1].y] = true;
                    copyFrom(original);
                }
            }
        }

        static bool destinationIsReached(Cfg cur, Cfg dest)
        {
            bool P = false;
            bool R = false;
            if ((cur.getX(0) == dest.getX(0)) && (cur.getY(0) == dest.getY(0)))
            {
                P = true;
            }
            if ((cur.getX(1) == dest.getX(1)) && (cur.getY(1) == dest.getY(1)))
            {
                R = true;
            }
            if (dest.getX(0) == -1)
            {
                P = true;
            }
            if (dest.getX(1) == -1)
            {
                R = true;
            }
            return P & R;
        }

        static void Main(string[] args)
        {
            Console.Write("Enter the dimensions: ");
            string[] strNumbers = Console.ReadLine().Split();
            // string[] text = System.IO.File.ReadAllLines("input.txt"); ;
            // string[] strNumbers = text[0].Split();
            sizeX = int.Parse(strNumbers[0]);
            sizeY = int.Parse(strNumbers[1]);

            // Read the map
            Console.WriteLine("Enter the map:");
            matrix = new char[sizeX, sizeY];
            string str;
            for (int j = 0; j < sizeY; j++)
            {
                str = Console.ReadLine();
                // str = text[j + 1];
                for (int i = 0; i < sizeX; i++)
                {
                    matrix[i, j] = str[i];
                }
            }

            // Parse the map
            visited = new bool[sizeX, sizeY, sizeX, sizeY];
            Cfg desiredCfg = new Cfg();
            Cfg currentCfg = new Cfg();
            bool found = false;
            for (int j = 0; j < sizeY; j++)
            {
                for (int i = 0; i < sizeX; i++)
                {
                    switch (matrix[i, j])
                    {
                        case '.':
                            break;

                        case '#':
                            for (int l = 0; l < sizeY; l++)
                            {
                                for (int k = 0; k < sizeX; k++)
                                {
                                    visited[i, j, k, l] = true;
                                    visited[k, l, i, j] = true;
                                }
                            }
                            break;

                        case 'P':
                            currentCfg.setX(0, i);
                            currentCfg.setY(0, j);
                            break;

                        case 'R':
                            currentCfg.setX(1, i);
                            currentCfg.setY(1, j);
                            break;

                        case '<':
                            desiredCfg.setX(0, i);
                            desiredCfg.setY(0, j);
                            found = true;
                            break;

                        case '>':
                            desiredCfg.setX(1, i);
                            desiredCfg.setY(1, j);
                            found = true;
                            break;

                        default:
                            Console.WriteLine("Invalid map.");
                            return;
                    }
                }
            }

            // Either < or > must be present
            if (!found)
            {
                Console.WriteLine("Invalid map.");
                return;
            }

            visited[currentCfg.getX(0), currentCfg.getY(0), currentCfg.getX(1), currentCfg.getY(1)] = true;

            // Find the solution
            Queue<Cfg> q = new Queue<Cfg>();
            while (!destinationIsReached(currentCfg, desiredCfg))
            {
                currentCfg.age++;
                currentCfg.check(ref q, 0);
                currentCfg.check(ref q, 1);
                if (q.Count == 0)
                {
                    Console.WriteLine("-1");
                    return;
                }
                currentCfg = q.Dequeue();
            }
            Console.WriteLine($"The answer is { currentCfg.age }.");
        }
    }
}
