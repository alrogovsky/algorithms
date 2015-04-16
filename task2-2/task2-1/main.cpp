//
//  main.cpp
//  task2-1
//
//  Created by Alexander Rogovsky on 11.04.15.
//  Copyright (c) 2015 Alexander Rogovsky. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>


struct CPoint{
    int X;
    int Y;
    CPoint(int x=0, int y=0) : Y(y), X(x) {}

    int getX() {return X;}
    int getY() {return Y;}
    
    void print()
    {
        std::cout<<X<<" "<<Y;
    }
};

bool IsBiggerThan(CPoint A, CPoint B) {
    
    if(A.X == B.X) {
        return A.Y > B.Y;
    }
    
    return A.X > B.X;
}

template < class T >
class CArray {
public:
    CArray( int size ) : bufferSize(size), realSize(0) { buffer = new T[size]; }
    ~CArray() { delete[] buffer; }
    int Size() { return realSize; }
    void Add( T p ) { buffer[realSize++] = p; }
    void swap(int index1, int index2);
    T operator[]( int i ) { return GetAt(i); }
    T GetAt( int index );
    void SetAt (int index, T p);
    T Last() { return buffer[realSize - 1]; }
    void DeleteLast() { realSize--; }
    bool IsEmpty() { return realSize == 0; }
    
    void print();
    
    
private:
    T* buffer;
    int bufferSize;
    int realSize;
};

template <class T>
void CArray<T>::print() {
    for(int i =0; i<bufferSize; i++)
    {
        buffer[i].print();
        std::cout<<" ";
    }
}

template <class T>
void CArray<T>::SetAt(int index, T p)
{
    assert(index < bufferSize);
    buffer[index] = p;
}

template <class T>
void CArray<T>::swap(int index1, int index2)
{
    T temp = buffer[index1];
    buffer[index1] = buffer[index2];
    buffer[index2] = temp;
}

template <class T>
void SiftDown( CArray<T>& A, int i )
{
    int left = 2*i+1;
    int right = 2*i+2;
    int biggest = i;
    
    if( left < A.Size() ) {
        if( IsBiggerThan(A[left], A[biggest]) )
            biggest = left;
    }
    
    if( right < A.Size() ) {
        if( IsBiggerThan(A[right], A[biggest]) )
            biggest = right;
    }
    
    if(biggest != i) {
        A.swap(i, biggest);
        SiftDown( A, biggest );
    }
    
}

template <class T>
void BuildHeap(CArray<T>& A)
{
    for (int i = A.Size() / 2 - 1; i>=0; i--) {
        SiftDown( A, i );
    }
    
}

template <class T>
T ExtractMax(CArray<T> &A) {
    assert( !A.IsEmpty() );
    T result = A[0];
    
    A.SetAt(0, A.Last());
    A.DeleteLast();
    
    if( !A.IsEmpty() ) {
        SiftDown( A, 0 );
    }
    
    return result;
}

template <class T>
void sortPoints( CArray<T> &A, int n) {
    
    BuildHeap(A);
    
    while ( A.Size() > 0 ) {
        
        T temp = A[0];
        A.SetAt(0, A.Last());
        A.SetAt(A.Size() - 1, temp);
        A.DeleteLast();
        
        if( !A.IsEmpty() ) {
            SiftDown( A, 0 );
        }
    }
    
}

template <class T>
T CArray<T>::GetAt(int index)
{
    assert( index < bufferSize);
    return buffer[index];
}




int main() {
    
    int n = 0;
    std::cin>>n;
    
    CArray<CPoint> A(n);
    
    int x = 0, y = 0;
    for(int i = 0; i < n; i++)
    {
        std::cin>>x>>y;
        A.Add(CPoint(x, y));
    }
    
    
    sortPoints(A, n);
    A.print();
    
    
    return 0;
}
