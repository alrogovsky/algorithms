/*
	Alexander Rogovsky
	APO-12

	Формат входных данных.
	В первой строке количество команд.
	Каждая команда задаётся как 2 целых числа: a b.
	a = 1 - push front
	a = 2 - pop front
	a = 3 - push back
	a = 4 - pop back
	Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
	Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
	Формат выходных данных.
	Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

	4_1. Реализовать очередь с динамическим буфером.
*/


#include <iostream>
#include <assert.h>

#define GROW_RATE 2

class CQueue {
public:
    CQueue(int size);
    ~CQueue() { delete[] buffer; }

    //Функции
    void Enqueue(int a);
    int Dequeue();

    //Проверка на пустоту
    bool IsEmpty() { return head == tail; }

    //Принт для тестов
    void print();

private:
    int* buffer;
    int bufferSize;
    int head;
    int tail;

    //Реаллокация
    void grow();
};

//Конструктор
CQueue::CQueue(int size) : bufferSize(size), head(0), tail(0)
{
    buffer = new int[bufferSize];
}

//Вход в очередь
void CQueue::Enqueue(int a)
{
    if ((tail + 1) % bufferSize == head)
        grow();

    buffer[tail] = a;
    tail = (tail + 1) % bufferSize;
}

//Выход из очереди
int CQueue::Dequeue()
{
    if (!IsEmpty()) {
        int result = buffer[head];
        head = (head + 1) % bufferSize;
        return result;
    }
    else {
        return -1;
    }
}

//Реаллокация
void CQueue::grow()
{
    //std::cout << "i'm in grow!!!\n\n";
    int newSize = bufferSize * GROW_RATE;
    int* new_buffer = new int[newSize];
    int newBufferSize = bufferSize * GROW_RATE;
    if (head < tail) {
        for (int i = 0; i < tail; i++) {
            new_buffer[i] = buffer[i];
        }
    }
    else {
        int current = 0;
        for (int i = 0; i < bufferSize - head; i++) {
            new_buffer[current] = buffer[head + i];
            current++;
        }
        for (int i = 0; i < tail; i++) {
            new_buffer[current] = buffer[i];
            current++;
        }
        head = 0;
        tail = current;
    }

    delete[] buffer;

    buffer = new_buffer;
    bufferSize = newBufferSize;

}

//Принт для тестов
void CQueue::print()
{
    std::cout << "printing for BUFF SIZE: " << bufferSize << " ///// head = " << head << " ///// tail = " << tail << "\n";
    for (int i = 0; i < bufferSize; i++)
    {
        std::cout << buffer[i] << " ";
    }

    std::cout << "\n\n\n";
}

bool IsPossible(CQueue &Q) {
    int n;
    std::cin >> n;
    if(n == 0) return false;

    bool answer = true;
    for (int i = 0; i < n; i++) {
        int command, value;
        std::cin >> command >> value;
        switch (command) {
            default: answer = false;
            case 2: {
                        int get = Q.Dequeue();
                        answer = answer && (value == get);
                        break;
            }
            case 3: {
                        Q.Enqueue(value);
                        break;
            }

        }
    }

    return answer;
}

int main()
{
    CQueue Q(4);

    if (IsPossible(Q)) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }

    return 0;
}
