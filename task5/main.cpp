#include <iostream>
#include <string.h>
#include <assert.h>

#define GROW_RATE 2

struct Rectangle {
    // размеры
    int height;
    int width;

    //Вычисление площади
    int getArea() { return height * width; }
    Rectangle( int w = 0, int h = 0 ) : height(h), width(w) {} ;
};


class CStack {
public:
    CStack( int a ) : bufferSize(a), realSize(0) { buffer = new Rectangle[a]; }
    ~CStack() { delete [] buffer; }
    void push(Rectangle a);
    Rectangle pop();

    //print
    void topPrint() { std::cout<<"\n H = " << topHeight() << " W = " << topWidth()<<"\n\n"; }

    //Быстро получить высоту
    int topHeight() { return buffer[realSize - 1].height; }

    //Ширину
    int topWidth() { return buffer[realSize - 1].width; }

    //Быстро увеличить ширину
    void increaseWidth(int a) { buffer[realSize - 1].width += a; }

    // Проверка на пустоту
    bool IsEmpty()  { return realSize == 0; };

private:
    Rectangle* buffer;
    int bufferSize;
    int realSize;

    //Realloc
    void grow();

};

// Добавление
void CStack::push(Rectangle a)
{
    if(realSize == bufferSize)
        grow();
    buffer[realSize++] = a;
}

Rectangle CStack::pop()
{
    assert(!IsEmpty());
    return buffer[--realSize];
}

// Reallocate
void CStack::grow()
{
    int newBufferSize = bufferSize * GROW_RATE;
    Rectangle* newBuffer = new Rectangle[newBufferSize];

    //Копируем стек
    memcpy(newBuffer, buffer, bufferSize * sizeof(Rectangle));

    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}


//Поиск максимума
int maxSquare(Rectangle* arr, int size)
{
    int max = arr[0].getArea();
    CStack S(1);
    S.push(arr[0]);

    for(int i = 1 ; i < size; i++) {
        if( arr[i].height >= S.topHeight() )
            S.push(arr[i]);
        else {
            //идем по высоте
            int currentHeight = S.topHeight();
            while( currentHeight > arr[i].height ) {
                Rectangle last = S.pop();
                int area = last.getArea();
                if (area > max)
                    max = area;

                // Пустой стек?
                if(S.IsEmpty())
                {
                    currentHeight = arr[i].height;
                    S.push(Rectangle(last.width + arr[i].width, currentHeight));
                }

                else {
                    S.increaseWidth(last.width);

                    if (S.topHeight() > arr[i].height)
                        currentHeight = S.topHeight();
                    else if( S.topHeight() == arr[i].height) {
                        S.increaseWidth(arr[i].width);
                        currentHeight = arr[i].height;
                    }
                    else{
                        currentHeight = arr[i].height;
                        S.push(Rectangle(last.width + arr[i].width, currentHeight));
                    }
                }
            }
        }
    }

    return max;
}


int main() {

    int n;
    std::cin >> n;
    Rectangle* arr = new Rectangle[n+1];

    int h, w;

    for( int i = 0; i < n; i++) {
        std::cin >> w >> h;
        arr[i] = Rectangle(w, h);
    }

    arr[n] = Rectangle(0, 0);

    std::cout << maxSquare(arr, n+1);

    delete [] arr;

    return 0;
}