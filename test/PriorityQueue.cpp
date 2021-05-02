#include "PriorityQueue.hpp"

template <typename T>
int PriorityQueue<T>::getParent(int index) const{
    if(index == 0){//0 == index
        return -1;
    }
    return (index-1)/2;//index%2 ? (index-1)/2 : (index-2)/2;
}
template <typename T>
int PriorityQueue<T>::getLeftChild(int index) const{
    int lChild = 2*index+1;
    if(lChild < size()){
        return lChild;
    }
    return -1;
}
template <typename T>
int PriorityQueue<T>::getRightChild(int index) const{
    int rChild = 2*index+2;
    if(rChild < size()){
        return rChild;
    }
    return -1;
}
    ///SIFT///
template <typename T>
void PriorityQueue<T>::swap(T& a, T& b) const{
    T temp = a;
    a = b;
    b = temp;
}
template <typename T>
void PriorityQueue<T>::siftUp(int index) const{
    int indexP = getParent(index);
    if(indexP != -1){
        if(*tree.get(indexP) < *tree.get(index)){
            swap(*tree.get(indexP), *tree.get(index));
            siftUp(indexP);
        }
    }
}
template <typename T>
void PriorityQueue<T>::siftDown(int index) const{
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
template <typename T>
void PriorityQueue<T>::push(const T& obj){
    tree.push_back(obj);
    siftUp(size()-1);
}
template <typename T>
void PriorityQueue<T>::pop(){
    if(!empty()){
        swap(*top(), *tree.get(size()-1));
        tree.pop_back();
        siftDown(0);
    }
}
///
template <typename T>
T* PriorityQueue<T>::top() const{
    //if(!empty()){
        return tree.get(0);
    //}
    //return NULL;
}

template <typename T>
bool PriorityQueue<T>::empty() const{
    return size()==0;
}

template <typename T>
void heapSort(T *array, int sizeOfArray){
    PriorityQueue<T> heap;
    heap.tree.capacity = sizeOfArray;
    heap.tree.realSize = sizeOfArray;
    heap.tree.innerArray = array;
    for(int i = heap.getParent(sizeOfArray-1); i > -1; i--){
        heap.siftDown(i);
    }
    for(int i = sizeOfArray-1; i > -1; i--){
        heap.swap(heap.tree.innerArray[0], heap.tree.innerArray[i]);
        heap.tree.realSize--;
        heap.siftDown(0);
    }
}

template void heapSort(int *, int);