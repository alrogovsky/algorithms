//
//  main.cpp
//  task2-6
//
//  Created by Alexander Rogovsky on 16.04.15.
//  Copyright (c) 2015 Alexander Rogovsky. All rights reserved.
//

#include <string.h>
#include <cstdio>
#define GROW_RATE 2
#define MAX_WORD_SIZE 256

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
        //assert
        if(index >= 0 && index < realSize)
            return buffer[index];
        else return buffer[0];
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

void MSDSort(CArray<char*> &A, int start, int end, int symbolNum)
{
    if(start == end-1)
        return;
    char minValue, maxValue;
    minValue = maxValue = A[start][symbolNum];
    
    // Ищем макс и мин
    for( int i = start; i < end; ++i ) {
        if ( A[i][symbolNum] < minValue ) minValue = A[i][symbolNum];
        if ( A[i][symbolNum] > maxValue ) maxValue = A[i][symbolNum];
    }
    if(minValue == 0 && maxValue == 0)
        return;
    
    // массив для индексов
    int valuesCount = maxValue - minValue + 1;
    int* valuesData = new int[valuesCount];
    ::memset(valuesData, 0, valuesCount * sizeof(int));
    
    // считаем сколько всего таких элементов
    for(int i = start; i < end; i++) {
        if(A[i][symbolNum] != 0)
            valuesData[A[i][symbolNum] - minValue]++;
        else
            valuesData[0]++;
    }
    
    // высчитываем конечные позиции элементов
    for( int i = 1; i < valuesCount; i++){
        valuesData[i] += valuesData[i - 1];
    }
    
    char** tempData = new char*[end - start + 1];
    
    //копируем с конца по указанным индексам
    for( int i = end - 1; i >= start; --i) {
        int valueIndex = A[i][symbolNum] - minValue;
        valuesData[valueIndex]--;
        tempData[valuesData[valueIndex]] = A[i];
    }
    
    for( int i = start, j = 0; i < end; ++i, ++j ) {
        A[i] = tempData[j];
    }
    
    /*
    for(int i = 0; i < A.Size(); i++) {
        std::cout<<A[i]<<"\n";
    }
    
    std::cout<<"START: "<<start<<"  END:"<<end<<"\n\n\n";
    std::cout<<"VALUESDATA: ";
    for(int i = 0; i<valuesCount; i++)
        std::cout<<valuesData[i]<<" ";
    
    std::cout<<"\n";
*/
    
    delete [] tempData;
    
    if( valuesCount > 1 )
    {
        for(int i = 1; i < valuesCount; i++)
        {
            // сортируем по группам элементов
            if(valuesData[i] != valuesData[i-1]) {
                MSDSort(A, start+valuesData[i-1], start+valuesData[i], symbolNum+1);
            }
        }
    }
    
    if( start+valuesData[valuesCount - 1] != end-1 ) {
        MSDSort(A, start+valuesData[valuesCount-1], end, symbolNum+1);
    }
    
    delete [] valuesData;
}

void MSDSortArray(CArray<char*> &A)
{
    MSDSort(A, 0, A.Size(), 0);
}



int main() {
    
    CArray<char*> A;
    
    char* word = new char[MAX_WORD_SIZE];
    while( scanf("%s", word) == 1 )
    {
        A.Add(word);
        word = new char[MAX_WORD_SIZE];
    }
    
    MSDSortArray(A);
    
    for ( int i = 0; i < A.Size(); ++i )
        printf("%s\n", A[i]);
    
    delete [] word;

    return 0;
}
