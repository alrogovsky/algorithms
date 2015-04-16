//
//  main.cpp
//  task2-3
//
//  Created by Alexander Rogovsky on 11.04.15.
//  Copyright (c) 2015 Alexander Rogovsky. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <string.h>
#define GROW_RATE 2

// Point class
struct CPoint{
    int value;
    int status;
    CPoint(int x=0, int stat=1) : value(x), status(stat) {}
};


bool operator<= (CPoint& point1, CPoint& point2)
{
    return point1.value <= point2.value;
}


// Array class

template <class T>
class CArray {
public:
    CArray( int size=100 ) : bufferSize(size), realSize(0) { buffer = new T[size]; }
    CArray(CArray<T>& arr, int start, int end);
    ~CArray() { delete[] buffer; }
    
    int Size() { return realSize; }
    void Add(T item);
    void DeleteAt(int index);
    
    T& operator [] (int index)
    {
        assert(index >= 0 && index < realSize);
        return buffer[index];
    }
    
private:
    
    void Realloc();
    
    T* buffer;
    int bufferSize;
    int realSize;
};

//Construct for merge

template< class T >
CArray<T>::CArray(CArray<T> &arr, int start, int end) : bufferSize(arr.Size()), realSize(0)
{
    buffer = new T[bufferSize];
    int last = arr.Size() - 1;
    if ( start < 0 )
        start = 0;
    else
        if ( start > last )
            start = last;
    if ( end > last)
        end = last;
    else
        if ( end < 0 )
            end = 0;
    for ( int i = start; i < end + 1; ++i )
        Add(arr[i]);
}

// Reallocate with growth
template <class T>
void CArray<T>::Realloc()
{
    int newBufferSize = bufferSize * GROW_RATE;
    T* newBuffer = new T[newBufferSize];
    
    //Копируем стек
    memcpy(newBuffer, buffer, bufferSize * sizeof(T));
        
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

// Add element
template <class T>
void CArray<T>::Add(T item)
{
    if(realSize == bufferSize)
        Realloc();
    buffer[realSize++] = item;
}

// Delete At Index
template <class T>
void CArray<T>::DeleteAt(int index)
{
    if ( index < 0 )
        return;
    for ( int i = index; i < realSize - 1; ++i )
        buffer[i] = buffer[i + 1];
    --realSize;
}



template < class T >
void mergeSort(CArray<T>& arr)
{
    if ( arr.Size() == 1 )
        return;
    
    CArray<T> half1(arr, 0, arr.Size() / 2 - 1);
    CArray<T> half2(arr, arr.Size() / 2, arr.Size() - 1);
    
    mergeSort(half1);
    mergeSort(half2);
    
    int j = 0, k = 0;
    for ( int i = 0; i < arr.Size(); ++i )
    {
        if ( j < half1.Size() && k < half2.Size() )
        {
            if ( half1[j] <= half2[k] )
            {
                arr[i] = half1[j];
                ++j;
            }
            else
            {
                arr[i] = half2[k];
                ++k;
            }
        }
        else
        {
            if ( j < half1.Size() )
            {
                arr[i] = half1[j];
                ++j;
            }
            else
            {
                arr[i] = half2[k];
                ++k;
            }
        }
    }
}


int calculateShading(CArray<CPoint>& A)
{
    int layer = 1;
    int count = 0;
    
    for(int i = 1; i < A.Size(); i++)
    {
        if(layer != 0)
            count+= A[i].value - A[i-1].value;
        
        layer += A[i].status;
    }
    
    return count;
}



int main() {
    
    CArray< CPoint > A;
    
    int n=0;
    std::cin>>n;
    
    int start, end;
    
    for(int i = 0; i < n; i++) {
        std::cin>>start>>end;
        A.Add(CPoint(start, 1));
        A.Add(CPoint(end, -1));
    }
    
    
    mergeSort(A);
    
    std::cout<<calculateShading(A);
    
    return 0;
}