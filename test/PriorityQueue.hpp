#ifndef _PRIORITYQUEUE_HPP
#define _PRIORITYQUEUE_HPP

struct Data{
    int hp;
    int damage;
    float skill;

    Data();

    bool operator< (const Data& e) const;
    bool operator> (const Data& e) const;
    bool operator== (const Data& e) const;
    bool operator<= (const Data& e) const;
    bool operator>= (const Data& e) const;
};

template <typename T>
class DynamicArray{
    public:
    int capacity = 1;
    int realSize = 0;
    const int alpha = 2;
    const int beta = 3; // decrease threshold, must be int
    T* innerArray = new T[capacity];

    void push_back(const T& t);
    void pop_back();
    T* get(const int n) const;
    int size() const;
    ~DynamicArray();
};

template <typename T>
class PriorityQueue{
    public:
    DynamicArray<T> tree;
    ///GET///
    int getParent(int index) const;
    int getLeftChild(int index) const;
    int getRightChild(int index) const;
    ///SIFT///
    void swap(T& a, T& b) const;
    void siftUp(int index) const;
    void siftDown(int index) const;
    ///
    void push(const T& obj);
    void pop();
    ///
    T* top() const;
    int size() const{
    return tree.size();
};
    bool empty() const;
};

template <typename T>
void heapSort(T *array, int sizeOfArray);

template <typename T>
float testPriorityQueueSpeed(T&& priorityQueue);

bool testPriorityQueue();

bool testHeapSort();

#endif
