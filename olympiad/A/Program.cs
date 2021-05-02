using System;
using System.Collections;
using System.Collections.Generic;

namespace A
{
    class Program
    {
        class Town
        {
            private List<Town> roads;
            private bool isVisited = false;
            public Town()
            {
                roads = new List<Town>();
            }
            public void addRoad(Town town)
            {
                roads.Add(town);
            }
            private void clearVisits()
            {
                if (!isVisited)
                {
                    return;
                }
                isVisited = false;
                foreach (Town t in roads)
                {
                    t.clearVisits();
                }
            }
            private Tuple<Town, int> findFarthest()
            {
                isVisited = true;

                // Find heights for every connected node and determine the highest one
                Tuple<Town, int> value;
                var maxValue = new Tuple<Town, int>(this, 0);
                foreach (var road in roads)
                {
                    if (road.isVisited)
                    {
                        continue;
                    }
                    value = road.findFarthest();
                    if (value.Item2 >= maxValue.Item2)
                    {
                        maxValue = value;
                    }
                }

                // Return the biggest height plus one
                return new Tuple<Town, int>(maxValue.Item1, maxValue.Item2 + 1);
            }
            public Tuple<Town, int> findBestRoute()
            {
                clearVisits();
                var iter1 = findFarthest();
                iter1.Item1.clearVisits();
                var iter2 = iter1.Item1.findFarthest();
                return iter2;
            }
            private bool __isConnected(Town t)
            {
                if (this == t)
                {
                    return true;
                }
                foreach (var road in roads)
                {
                    if (!road.isVisited)
                    {
                        road.isVisited = true;
                        if (road == t)
                        {
                            return true;
                        }
                        if (road.__isConnected(t))
                        {
                            return true;
                        }
                    }
                }
                return false;
            }
            public bool isConnected(Town t)
            {
                clearVisits();
                return __isConnected(t);
            }
        }
        static void Main(string[] args)
        {
            // Enter number of towns n and number of roads m
            Console.Write("Enter n and m: ");
            string[] tokens = Console.ReadLine().Split();
            // string[] text = System.IO.File.ReadAllLines("input.txt");
            // string[] tokens = text[0].Split();
            int n = int.Parse(tokens[0]);
            int m = int.Parse(tokens[1]);

            var towns = new Town[n];
            for (int i = 0; i < n; i++)
            {
                towns[i] = new Town();
            }

            // Read all the roads
            int ind1, ind2;
            for (int i = 0; i < m; i++)
            {
                tokens = Console.ReadLine().Split();
                // tokens = text[i + 1].Split();
                ind1 = int.Parse(tokens[0]) - 1;
                ind2 = int.Parse(tokens[1]) - 1;
                towns[ind1].addRoad(towns[ind2]);
                towns[ind2].addRoad(towns[ind1]);
            }

            // Find the longest route on every island
            var routes = new Hashtable();
            Tuple<Town, int> current;
            bool isPresent;
            foreach (Town t1 in towns)
            {
                isPresent = false;
                current = t1.findBestRoute();
                foreach (Town t2 in routes.Keys)
                {
                    if (current.Item1.isConnected(t2))
                    {
                        isPresent = true;
                    }
                    if (isPresent)
                    {
                        break;
                    }
                }
                if (!isPresent)
                {
                    routes.Add(current.Item1, current.Item2);
                }
            }

            // Add them
            int routeLength = 0;
            foreach (int len in routes.Values)
            {
                routeLength += len;
            }

            // Output the answer
            Console.WriteLine(routeLength);
        }
    }
}
