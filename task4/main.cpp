#include <iostream>
#include <assert.h>

#define GROW_RATE 2

class CQueue {
public:
    CQueue( int size );
    ~CQueue() { delete[] buffer; }

    //Функции
    void Enqueue(int a);
    int Dequeue();

    //Проверка на пустоту
    bool IsEmpty() { return head==tail; }

private:
    int* buffer;
    int bufferSize;
    int head;
    int tail;

    //Реаллокация
    void grow();
};

CQueue::CQueue( int size ) : bufferSize(size), head(0), tail(0)
{
    buffer = new int[bufferSize];
}

void CQueue::Enqueue(int a)
{
    if( ( tail + 1 ) % bufferSize == head)
        grow();

    buffer[tail] = a;
    ++tail;
    std::cout<<tail;
}

int CQueue::Dequeue()
{
    assert( head != tail );
    int result = buffer[head];
    head = (head+1) % bufferSize;
    return result;
}

void CQueue::grow()
{
    std::cout<<"POPAL!";
    int newSize = bufferSize * GROW_RATE;
    int* new_buffer = new int[newSize];


}

int main()
{
    CQueue Q(2);
    Q.Enqueue(10);
    Q.Enqueue(5);
    Q.Enqueue(44);
    return 0;
}

