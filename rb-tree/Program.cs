using System;
using System.Diagnostics;
using System.Text;
using System.Collections.Generic;

namespace rb_tree
{
    class Program
    {
        class RBTree<T> where T : IComparable
        {
            private enum Color
            {
                Black, Red
            }
            private class Node
            {
                public static Node nil = new Node();
                public T key;
                public Node left, right, parent;
                public Color color;
                public Node()
                {
                    left = right = parent = nil;
                    color = Color.Black;
                }
                public Node(T key)
                {
                    left = right = parent = nil;
                    color = Color.Red;
                    this.key = key;
                }
                public int getHeight()
                {
                    if (this == nil)
                    {
                        return 0;
                    }
                    return Math.Max(left.getHeight(), right.getHeight()) + 1;
                }
                public int getSize()
                {
                    if (this == nil)
                    {
                        return 0;
                    }
                    return left.getSize() + right.getSize() + 1;
                }
                public Node findMin()
                {
                    Node x, y;
                    x = y = this;
                    while (x != nil)
                    {
                        y = x;
                        x = x.left;
                    }
                    return y;
                }
                public Node findMax()
                {
                    Node x, y;
                    x = y = this;
                    while (x != nil)
                    {
                        y = x;
                        x = x.right;
                    }
                    return y;
                }
            }
            static private Node nil = Node.nil;
            private Node root;
            public RBTree()
            {
                root = nil;
            }
            public RBTree(T key)
            {
                root = new Node(key);
            }
            public int getHeight()
            {
                return root.getHeight();
            }
            public int getSize()
            {
                return root.getSize();
            }
            public bool find(T x)
            {
                return __find(x) != nil;
            }
            private Node __find(T key)
            {
                Node x = root;
                while ((x != nil) && (key.CompareTo(x.key) != 0))
                {
                    if (key.CompareTo(x.key) < 0)
                    {
                        x = x.left;
                    }
                    else
                    {
                        x = x.right;
                    }
                }
                return x;
            }
            // public T[] findInRange()
            // {

            // }
            public bool insert(T key)
            {
                Node y = nil;
                Node x = root;
                while (x != nil)
                {
                    y = x;
                    if (key.CompareTo(x.key) == 0)
                    {
                        return false;
                    }
                    if (key.CompareTo(x.key) < 0)
                    {
                        x = x.left;
                    }
                    else
                    {
                        x = x.right;
                    }
                }
                Node z = new Node(key);
                z.parent = y;
                if (y == nil)
                {
                    z.color = Color.Black;
                    root = z;
                }
                else if (key.CompareTo(y.key) < 0)
                {
                    y.left = z;
                }
                else
                {
                    y.right = z;
                }
                insertFixup(z);
                return true;
            }
            private void leftRotate(Node x)
            {
                Node y = x.right;
                x.right = y.left;
                if (y.left != nil)
                {
                    y.left.parent = x;
                }
                y.parent = x.parent;
                if (x.parent == nil)
                {
                    root = y;
                }
                else if (x == x.parent.left)
                {
                    x.parent.left = y;
                }
                else
                {
                    x.parent.right = y;
                }
                y.left = x;
                x.parent = y;
            }
            private void rightRotate(Node x)
            {
                Node y = x.left;
                x.left = y.right;
                if (y.right != nil)
                {
                    y.right.parent = x;
                }
                y.parent = x.parent;
                if (x.parent == nil)
                {
                    root = y;
                }
                else if (x == x.parent.left)
                {
                    x.parent.left = y;
                }
                else
                {
                    x.parent.right = y;
                }
                y.right = x;
                x.parent = y;
            }
            private void insertFixup(Node z)
            {
                while (z.parent.color == Color.Red)
                {
                    if (z.parent == z.parent.parent.left)
                    {
                        Node y = z.parent.parent.right;
                        if (y.color == Color.Red)
                        {
                            z.parent.color = Color.Black;
                            y.color = Color.Black;
                            z.parent.parent.color = Color.Red;
                            z = z.parent.parent;
                        }
                        else
                        {
                            if (z == z.parent.right)
                            {
                                z = z.parent;
                                leftRotate(z);
                            }
                            z.parent.color = Color.Black;
                            z.parent.parent.color = Color.Red;
                            rightRotate(z.parent.parent);
                        }
                    }
                    else
                    {
                        Node y = z.parent.parent.left;
                        if (y.color == Color.Red)
                        {
                            z.parent.color = Color.Black;
                            y.color = Color.Black;
                            z.parent.parent.color = Color.Red;
                            z = z.parent.parent;
                        }
                        else
                        {
                            if (z == z.parent.left)
                            {
                                z = z.parent;
                                rightRotate(z);
                            }
                            z.parent.color = Color.Black;
                            z.parent.parent.color = Color.Red;
                            leftRotate(z.parent.parent);
                        }
                    }
                    root.color = Color.Black;
                }
            }
            public bool delete(T key)
            {
                Node x;
                Node z = __find(key);
                if (z == nil)
                {
                    return false;
                }
                Node y = z;
                Color yOriginalColor = y.color;
                if (z.left == nil)
                {
                    x = z.right;
                    transplant(z, z.right);
                }
                else if (z.right == nil)
                {
                    x = z.left;
                    transplant(z, z.left);
                }
                else
                {
                    y = z.right.findMin();
                    yOriginalColor = y.color;
                    x = y.right;
                    if (y.parent == z)
                    {
                        x.parent = y;
                    }
                    else
                    {
                        transplant(y, y.right);
                        y.right = z.right;
                        y.right.parent = y;
                    }
                    transplant(z, y);
                    y.left = z.left;
                    y.left.parent = y;
                    y.color = z.color;
                }
                if (yOriginalColor == Color.Black)
                {
                    deleteFixup(x);
                }
                return true;
            }
            private void transplant(Node u, Node v)
            {
                if (u.parent == nil)
                {
                    root = v;
                }
                else if (u == u.parent.left)
                {
                    u.parent.left = v;
                }
                else
                {
                    u.parent.right = v;
                }
                v.parent = u.parent;
            }
            private void deleteFixup(Node x)
            {
                while ((x != root) && (x.color == Color.Black))
                {
                    if (x == x.parent.left)
                    {
                        Node w = x.parent.right;
                        if (w.color == Color.Red)
                        {
                            w.color = Color.Black;
                            x.parent.color = Color.Red;
                            leftRotate(x.parent);
                            w = x.parent.right;
                        }
                        if ((w.left.color == Color.Black) && (w.right.color == Color.Black))
                        {
                            w.color = Color.Red;
                            x = x.parent;
                        }
                        else
                        {
                            if (w.right.color == Color.Black)
                            {
                                w.left.color = Color.Black;
                                w.color = Color.Red;
                                rightRotate(w);
                                w = x.parent.right;
                            }
                            w.color = x.parent.color;
                            x.parent.color = Color.Black;
                            w.right.color = Color.Black;
                            leftRotate(x.parent);
                            x = root;
                        }
                    }
                    else
                    {
                        Node w = x.parent.left;
                        if (w.color == Color.Red)
                        {
                            w.color = Color.Black;
                            x.parent.color = Color.Red;
                            rightRotate(x.parent);
                            w = x.parent.left;
                        }
                        if ((w.left.color == Color.Black) && (w.right.color == Color.Black))
                        {
                            w.color = Color.Red;
                            x = x.parent;
                        }
                        else
                        {
                            if (w.left.color == Color.Black)
                            {
                                w.right.color = Color.Black;
                                w.color = Color.Red;
                                leftRotate(w);
                                w = x.parent.left;
                            }
                            w.color = x.parent.color;
                            x.parent.color = Color.Black;
                            w.left.color = Color.Black;
                            rightRotate(x.parent);
                            x = root;
                        }
                    }
                }
                x.color = Color.Black;
            }
        }
        static string generateRandString(int minLength, int maxLength)
        {
            Random rand = new Random();
            int len = rand.Next(minLength, maxLength);
            StringBuilder stringBuilder = new StringBuilder(len);
            for (int i = 0; i < len; i++)
            {
                stringBuilder.Append((char)rand.Next('a', 'z'));
            }
            return stringBuilder.ToString();
        }
        class Data : IComparable
        {
            public string name;
            public double score;
            public double willingness;
            public int copiedWorks;
            public Data()
            {
                Random rand = new Random();
                name = generateRandString(4, 12);
                score = rand.NextDouble();
                willingness = rand.NextDouble();
                copiedWorks = rand.Next(21);
            }
            public int CompareTo(object obj)
            {
                if (obj == null)
                {
                    return 1;
                }
                Data data = obj as Data;
                if (data != null)
                {
                    return this.name.CompareTo(data.name);
                }
                else
                {
                    throw new ArgumentException("Object is not of Data type");
                }
            }
        }
        static long generateRandLong()
        {
            Random rand = new Random();
            long randLong = rand.Next() << 32;
            randLong += rand.Next();
            return randLong;
        }
        static void testRBTree()
        {
            var rand = new Random();

            const int iters = 80000;
            const int keysAmount = iters * 2;
            // const int itersToRangeQueries = 1000;

            // T = int
            Data[] data = new Data[keysAmount];
            for (int i = 0; i < keysAmount; i++)
            {
                data[i] = new Data();
            }

            Data[] dataToInsert = new Data[iters];
            Data[] dataToErase = new Data[iters];
            Data[] dataToFind = new Data[iters];
            // Tuple<int, int>[] dataToRangeQueries = new Tuple<int, int>[];
            // ...

            for (int i = 0; i < iters; i++)
            {
                dataToInsert[i] = data[generateRandLong() % keysAmount];
                dataToErase[i] = data[generateRandLong() % keysAmount];
                dataToFind[i] = data[generateRandLong() % keysAmount];
            }

            Stopwatch sw = new Stopwatch();
            RBTree<Data> myTree = new RBTree<Data>();
            sw.Start();
            for (int i = 0; i < iters; i++)
            {
                myTree.insert(dataToInsert[i]);
            }
            int myInsertSize = myTree.getSize();

            int myTreeHeight = myTree.getHeight();
            int optimalTreeHeight = (int)Math.Log2(myInsertSize) + 1;
            Console.WriteLine($"{ myInsertSize } { myTreeHeight } { optimalTreeHeight }");
            for (int i = 0; i < iters; i++)
            {
                myTree.delete(dataToErase[i]);
            }
            int myEraseSize = myInsertSize - myTree.getSize();
            int myFoundAmount = 0;
            for (int i = 0; i < iters; i++)
            {
                if (myTree.find(dataToFind[i]))
                {
                    myFoundAmount++;
                }
            }
            sw.Stop();
            var myTime = sw.Elapsed;

            sw = new Stopwatch();
            var set = new SortedSet<Data>();
            sw.Start();
            for (int i = 0; i < iters; i++)
            {
                set.Add(dataToInsert[i]);
            }
            int setInsertSize = set.Count;

            for (int i = 0; i < iters; i++)
            {
                set.Remove(dataToErase[i]);
            }
            int setEraseSize = setInsertSize - set.Count;
            int setFoundAmount = 0;
            for (int i = 0; i < iters; i++)
            {
                if (set.Contains(dataToFind[i]))
                {
                    setFoundAmount++;
                }
            }
            sw.Stop();
            var setTime = sw.Elapsed;

            Console.WriteLine($"My RBTree: height = { myTreeHeight }, optimal height = { optimalTreeHeight }");
            Console.WriteLine($"My time: { myTime }, size: { myInsertSize } - { myEraseSize }, found amount: { myFoundAmount }");
            Console.WriteLine($"Set time: { setTime }, size: { setInsertSize } - { setEraseSize }, found amount: { setFoundAmount }");
        }
        static void Main(string[] args)
        {
            testRBTree();
        }
    }
}
