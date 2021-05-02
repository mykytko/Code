#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string word, buf;
    ifstream ifs("file.txt", ios::in);
    cin >> word;
    int counter = 0;
    while (ifs >> buf) if (buf == word) counter++;
    cout << counter << endl;
    ifs.close();
}

/*#include <iostream>
#include <queue>
#include <algorithm>
#define COMPARE damage //hp/damage/skill

using namespace std;

struct Data{
    int hp;
    int damage;
    float skill;

    Data(){
        hp = rand()%100+1;
        damage = rand()%100+1;
        skill = rand()/1000.0;
    }

    bool operator< (const Data& e) const{
        return COMPARE < e.COMPARE;
    }
    bool operator> (const Data& e) const{
        return e<(*this); //A const member function can be called by any type of object. Non-const functions can be called by non-const objects only.
    }
    bool operator== (const Data& e) const{
        return COMPARE == e.COMPARE;
    }
    bool operator<= (const Data& e) const{
        return (*this) < e ? true : (*this) == e;
    }
    bool operator>= (const Data& e) const{
        return (*this) > e ? true : (*this) == e;
    }
};

template <typename T>
struct DynamicArray{
    int capacity = 1;
    int realSize = 0;
    const int alpha = 2;
    const int beta = 3; // decrease threshold, must be int
    T* innerArray = new T[capacity];

    void push_back(const T& t){
        if(size() == capacity){
            capacity *= alpha;
            T* innerArrayTemp = new T[capacity];
            for(int i = 0; i < size(); i++){
                innerArrayTemp[i] = innerArray[i];
            }
            delete[] innerArray;
            innerArray = innerArrayTemp;
        }
        innerArray[realSize++] = t; // "=" first, then "++"
    }
    void pop_back(){
        if(size() < capacity/beta){ // if <30%, when beta = 3
            capacity /= beta;
            T* innerArrayTemp = new T[capacity];
            for(int i = 0; i < size(); i++){
                innerArrayTemp[i] = innerArray[i];
            }
            delete[] innerArray;
            innerArray = innerArrayTemp;
        }
        realSize--;
    }
    T* get(const int n) const{
        //if((n<size()) && (n>-1)){
            return &innerArray[n];
        //}
        //return NULL;
    }
    int size() const{
        return realSize;
    }
    ~DynamicArray(){
        delete[] innerArray;
    }
};

template <typename T>
struct PriorityQueue{
    DynamicArray<T> tree = DynamicArray<T>();
    ///GET///
    int getParent(int index) const{
        if(index == 0){//0 == index
            return -1;
        }
        return (index-1)/2;//index%2 ? (index-1)/2 : (index-2)/2;
    }
    int getLeftChild(int index) const{
        int lChild = 2*index+1;
        if(lChild < size()){
            return lChild;
        }
        return -1;
    }
    int getRightChild(int index) const{
        int rChild = 2*index+2;
        if(rChild < size()){
            return rChild;
        }
        return -1;
    }
    ///SIFT///
    void swap(T& a, T& b) const{
        T temp = a;
        a = b;
        b = temp;
    }
    void siftUp(int index) const{
        int indexP = getParent(index);
        if(indexP != -1){
            if(*tree.get(indexP) < *tree.get(index)){
                swap(*tree.get(indexP), *tree.get(index));
                siftUp(indexP);
            }
        }
    }
    void siftDown(int index) const{
        int maxIndex = index;
        int indexL = getLeftChild(index);
        int indexR = getRightChild(index);
        if(indexL != -1){
            if(*tree.get(maxIndex) < *tree.get(indexL)){
                maxIndex = indexL;
            }
            if(indexR != -1){
                if(*tree.get(maxIndex) < *tree.get(indexR)){
                    maxIndex = indexR;
                }
            }
        }
        if(maxIndex != index){
            swap(*tree.get(maxIndex), *tree.get(index));
            siftDown(maxIndex);
        }
    }
    ///
    void push(const T& obj){
        tree.push_back(obj);
        siftUp(size()-1);
    }
    void pop(){
        if(!empty()){
            swap(*top(), *tree.get(size()-1));
            tree.pop_back();
            siftDown(0);
        }
    }
    ///
    T* top() const{
        //if(!empty()){
            return tree.get(0);
        //}
        //return NULL;
    }
    int size() const{
        return tree.size();
    }
    bool empty() const{
        return size()==0;
    }
};

template <typename T>
void heapSort(T *array, int sizeofArray){
    PriorityQueue<T> heap;
    heap.tree.capacity = sizeofArray;
    heap.tree.realSize = sizeofArray;
    heap.tree.innerArray = array;
    for(int i = heap.getParent(sizeofArray-1); i > -1; i--){
        heap.siftDown(i);
    }
    for(int i = sizeofArray-1; i > -1; i--){
        heap.swap(heap.tree.innerArray[0], heap.tree.innerArray[i]);
        heap.tree.realSize--;
        heap.siftDown(0);
    }
}

template <typename T>
float testPriorityQueueSpeed(T&& priorityQueue)//&& allows to pass temp object to a function
{
    const int iters = 100000;

    clock_t timeStart = clock();
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            priorityQueue.push(Data());
        }

        priorityQueue.top();
        priorityQueue.pop();
    }
    clock_t timeEnd = clock();
    float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;

    return time;
}

bool testPriorityQueue()
{
    const int iters = 20000;

    PriorityQueue<Data> myPriorQueue;
    priority_queue<Data> stlPriorQueue;

    bool isDataEqual = true;
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            Data randData = Data();
            myPriorQueue.push(randData);
            stlPriorQueue.push(randData);
        }

        if (!((*myPriorQueue.top()) == stlPriorQueue.top()))
        {
            isDataEqual = false;
            cerr << "Comparing eofed on iteration " << i << endl << endl;
            break;
        }
        int removeDataAmount = rand() % insertDataAmount;
        for (int j = 0; j < removeDataAmount; j++)
        {
            myPriorQueue.pop();
            stlPriorQueue.pop();
        }
    }

    int myQueueSize = myPriorQueue.size();
    int stlQueueSize = stlPriorQueue.size();

    float stlTime = testPriorityQueueSpeed<priority_queue<Data>>(priority_queue<Data>());
    float myTime = testPriorityQueueSpeed<PriorityQueue<Data>>(PriorityQueue<Data>());

    cout << "My PriorityQueue:" << endl;
    cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
    cout << "STL priority_queue:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl << endl;

    if (isDataEqual && myQueueSize == stlQueueSize)
    {
        cout << "The lab is completed" << endl << endl;
        return true;
    }

    cerr << ":(" << endl << endl;
    return false;
}

bool testHeapSort(){
    const int iters = 250000;

    int arrayForMySort[iters];
    int arrayForSTLSort[iters];

    bool isArraysEqual = true;

    for(int i = 0; i < iters; i++){
        arrayForMySort[i] = rand()%iters;
        arrayForSTLSort[i] = arrayForMySort[i];
    }

    clock_t myTimeStart = clock();
    heapSort(arrayForMySort, iters);
    clock_t myTimeEnd = clock();
    float myTime = (float(myTimeEnd - myTimeStart)) / CLOCKS_PER_SEC;

    clock_t stlTimeStart = clock();
    sort(arrayForSTLSort, arrayForSTLSort+iters);
    clock_t stlTimeEnd = clock();
    float stlTime = (float(stlTimeEnd - stlTimeStart)) / CLOCKS_PER_SEC;

    for(int i = 0; i < iters; i++){
        if(arrayForMySort[i] != arrayForSTLSort[i]){
            isArraysEqual = false;
            cerr << "Comparing eofed on iteration " << i << endl << endl;
            break;
        }
    }

    cout << "My HeapSort:" << endl;
    cout << "Time: " << myTime << endl;
    cout << "STL HeapSort:" << endl;
    cout << "Time: " << stlTime << endl << endl;

    if(!isArraysEqual){
        cerr << ":(" << endl << endl;
        return false;
    }

    cout<<"Work with sorted array:"<<endl;
    isArraysEqual = true;

    myTimeStart = clock();
    heapSort(arrayForMySort, iters);
    myTimeEnd = clock();
    myTime = (float(myTimeEnd - myTimeStart)) / CLOCKS_PER_SEC;

    stlTimeStart = clock();
    sort(arrayForSTLSort, arrayForSTLSort+iters);
    stlTimeEnd = clock();
    stlTime = (float(stlTimeEnd - stlTimeStart)) / CLOCKS_PER_SEC;

    for(int i = 0; i < iters; i++){
       if(arrayForMySort[i] != arrayForSTLSort[i]){
            isArraysEqual = false;
            cerr << "Comparing eofed on iteration " << i << endl << endl;
            break;
        }
    }

    cout << "My HeapSort:" << endl;
    cout << "Time: " << myTime << endl;
    cout << "STL HeapSort:" << endl;
    cout << "Time: " << stlTime << endl << endl;

    if(!isArraysEqual){
        cerr << ":(" << endl << endl;
        return false;
    }

    cout << "The additional task is completed" << endl << endl;
    return true;
}*/

// int main()
// {
//     srand(time(NULL));
//     testPriorityQueue();
//     testHeapSort();
//     return 0;
// }
