/*
3_4. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
Время работы поиска для каждого элемента B[i]: O(log(k)).
*/

#include <iostream>

int binarySearch(int*, int, int);
void print(int*, int, int*, int);

int main() {

    // Объявим переменные для размера массивов
    int n=0, m=0;

    // Соберем первый массив
    std::cin >> n;
    int* A = new int[n];

    for(int i = 0; i < n; i++) {
        std::cin >> A[i];
    }

    // Соберем второй массив
    std::cin >> m;
    int* B = new int[m];

    for(int i = 0; i < m; i++) {
        std::cin >> B[i];
    }

    print(A, n, B, m);


    //Очистим память
    delete [] B;
    delete [] A;

    return 0;
}

int binarySearch(int* arr, int count, int el) {
    int first = 0;
    int last = count;
    while(first < last){
        int mid = (first + last) / 2;
        if(el <= arr[mid])
            last = mid;
        else
            first = mid + 1;
    }


    //hardcode
    if(first == 1 && arr[first] < el) return first - 1;
    if(first == 0) return first;

    //Ищем полусумму
    int halfSum = (arr[first] + arr[first-1]) / 2;
    //сравниваем и возвращаем
    return halfSum < el ? first : first-1;
}

void print(int* A, int n, int* B, int m) {

    for(int i = 0; i < m; i++) {
        int el = B[i];
        int k = 0;

        //идем по степеням двойки
        for(int j = 0; j < n; j == 0 ? j++ : j *= 2) {
            if(A[j]>=el) {
                break;
            }
            k = j;
        }

        //получаем размер для поиска
        int delta = 0;
        if(2*k+1 > n) {
            delta=n-k;
        } else {
            delta = k+1;
        }

        //уходим в бин поиск
        int res = binarySearch(A+k, delta, el)+k;

        std::cout<<res<<" ";
    }
}