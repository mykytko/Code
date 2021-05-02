#include "PriorityQueue.hpp"
#include <cstdlib>

template <typename T>
void DynamicArray<T>::push_back(const T& t){
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
template <typename T>
void DynamicArray<T>::pop_back(){
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
template <typename T>
T* DynamicArray<T>::get(const int n) const{
    //if((n<size()) && (n>-1)){
        return &innerArray[n];
    //}
    //return NULL;
}
template <typename T>
int DynamicArray<T>::size() const{
    return realSize;
}
template <typename T>
DynamicArray<T>::~DynamicArray(){
    delete[] innerArray;
}

template class DynamicArray<int>;
template class DynamicArray<Data>;