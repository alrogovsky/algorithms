#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>


class CArray {
public:
    CArray( int size ) : bufferSize(size), realSize(0) { buffer = new int[size]; }
    ~CArray() { delete[] buffer; }
    int Size() { return realSize; }
    void Add( int num ) { buffer[realSize++] = num; }
    void swap(int index1, int index2);
    int operator[]( int i ) { return GetAt(i); }
    int GetAt( int index );
    void SetAt (int index, int val);
    void IncreaseFirst( int value ) { buffer[0]+= value; }
    int Last() { return buffer[realSize - 1]; }
    void DeleteLast() { realSize--; }
    bool IsEmpty() { return realSize == 0; }

private:
    int* buffer;
    int bufferSize;
    int realSize;
};

void CArray::swap(int index1, int index2)
{
    int temp = buffer[index1];
    buffer[index1] = buffer[index2];
    buffer[index2] = temp;
}

void CArray::SetAt(int index, int val)
{
    assert(index < bufferSize);
    buffer[index] = val;
}

// Получить элемент по индексу
int CArray::GetAt(int index)
{
    assert( index < bufferSize);
    return buffer[index];
}

// Просеивание
void SiftDown( CArray& A, int i )
{
    int left = 2*i+1;
    int right = 2*i+2;
    int least = i;

    if( left < A.Size() && A[left] < A[least] )
        least = left;
    if( right < A.Size() && A[right] < A[least])
        least = right;

    if(least != i) {
        A.swap(i, least);
        SiftDown( A, least );
    }

}

// Привести к куче
void BuildHeap(CArray& A)
{
    for (int i = A.Size() / 2 - 1; i>=0; i--) {
        SiftDown( A, i );
    }

}

// Вытащить минимум
int ExtractMin(CArray &A) {
    assert( !A.IsEmpty() );
    int result = A[0];

    A.SetAt(0, A.Last());
    A.DeleteLast();

    if( !A.IsEmpty() ) {
        SiftDown( A, 0 );
    }

    return result;
}

// Вычисление минимума
int computeMin( CArray &A ) {

    int sum = 0;

    while ( A.Size() > 1 ) {
        int min = ExtractMin( A );
        A.IncreaseFirst(min);
        sum += A[0];
        SiftDown(A, 0);
    }

    return sum;

}


int main() {

    int n;
    std::cin >> n;
    CArray A(n);

    int num;
    for(int i = 0; i < n; i++) {
        std::cin >> num;
        A.Add(num);
    }

    BuildHeap( A );

    int result = computeMin( A );
    std::cout << result;

    return 0;
}