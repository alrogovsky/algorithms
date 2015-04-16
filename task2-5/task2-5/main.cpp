//
//  main.cpp
//  task2-5
//
//  Created by Alexander Rogovsky on 16.04.15.
//  Copyright (c) 2015 Alexander Rogovsky. All rights reserved.
//

#include <string.h>
#include <iostream>
#include <cstdio>
#include <assert.h>
#include <stdint.h>
#define GROW_RATE 2

///////////// start CArray //////////////

template <class T>
class CArray {
public:
    CArray( int size=10 ) : bufferSize(size), realSize(0) { buffer = new T[size]; }
    //CArray(CArray<T>& arr, int start, int end);
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

template <class T>
void CArray<T>::Realloc()
{
    int newBufferSize = bufferSize * GROW_RATE;
    T* newBuffer = new T[newBufferSize];
    
    memcpy(newBuffer, buffer, bufferSize * sizeof(T));
    
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

// добавление элемента
template <class T>
void CArray<T>::Add(T item)
{
    if(realSize == bufferSize)
        Realloc();
    buffer[realSize++] = item;
}

// удаление элемента
template <class T>
void CArray<T>::DeleteAt(int index)
{
    if ( index < 0 )
        return;
    for ( int i = index; i < realSize - 1; ++i )
        buffer[i] = buffer[i + 1];
    --realSize;
}

///////////// end CArray /////////////////


template< class T >
int64_t mergeSort(CArray<T>& A);

template< class T >
int64_t splitAndMerge(CArray<T>& A, int start, int end, CArray<T>& buffer);

int main()
{
    CArray<int> A;
    
    int temp;
    while ( scanf("%d", &temp) == 1 )
    {
        A.Add(temp);
        std::cout<<A.Size();
    }
    
    int64_t inv = mergeSort(A);
    printf("%ld", inv);
    return 0;
}


template< class T >
int64_t mergeSort(CArray<T>& A)
{
    CArray<T> buf(A.Size());
    int64_t inv = splitAndMerge(A, 0, A.Size() - 1, buf);
    return inv;
}


template< class T >
int64_t splitAndMerge(CArray<T>& A, int start, int end, CArray<T>& buffer)
{
    if ( end - start == 0 )
        return 0;
    
    int half1_end = (end - start) / 2 + start;
    int half2_start = half1_end + 1;
    int64_t inv1 = splitAndMerge(A, start, half1_end, buffer);
    int64_t inv2 = splitAndMerge(A, half2_start, end, buffer);
    
    int64_t inv3 = 0;
    int j = start;
    int k = half2_start;
    for ( int i = start; i <= end; ++i )
    {
        if ( j <= half1_end && k <= end )
        {
            if ( A[j] <= A[k] )
            {
                buffer[i] = A[j];
                ++j;
            }
            else
            {
                inv3 += (half1_end - j + 1);
                buffer[i] = A[k];
                ++k;
            }
        }
        else
        {
            if ( j <= half1_end )
            {
                buffer[i] = A[j];
                ++j;
            }
            else
            {
                buffer[i] = A[k];
                ++k;
            }
        }
    }
    
    for ( int i = start; i <= end; ++i )
    {
        A[i] = buffer[i];
    }
    
    return inv1 + inv2 + inv3;
}

