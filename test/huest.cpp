#include "PriorityQueue.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <algorithm>

using namespace std;

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
            cerr << "Comparing failed on iteration " << i << endl << endl;
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
            cerr << "Comparing failed on iteration " << i << endl << endl;
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
            cerr << "Comparing failed on iteration " << i << endl << endl;
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
}
