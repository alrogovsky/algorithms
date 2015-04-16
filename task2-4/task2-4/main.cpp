//
//  main.cpp
//  task2-4
//
//  Created by Alexander Rogovsky on 12.04.15.
//  Copyright (c) 2015 Alexander Rogovsky. All rights reserved.
//

#include <iostream>
#include <cmath>

int partition(int* &arr, int start, int end)
{
    if(start == end)
        return start;
    
    int middle = (end-start)/2;
    int average = ( arr[start] + arr[end] + arr[middle] ) / 3;
    
    int pivot;
    
    if( std::abs(arr[start] - average) < std::abs(arr[middle] - average) ) {
        pivot = std::abs(arr[start] - average) < std::abs(arr[end] - average) ? start : end;
    } else {
        pivot = std::abs(arr[middle] - average) < std::abs(arr[end] - average) ?  middle : end;

    }
    
    std::swap(arr[pivot], arr[end]);
    pivot = end;
    
    int i = start;
    int j = i;
    
    while(j < end) {
        
        if(arr[j] <= arr[pivot]) {
            std::swap(arr[i],arr[j]);
            ++i;
            ++j;
        }
        
        while( arr[j] > arr[pivot] ) ++j;
    }
    std::swap(arr[i], arr[pivot]);
    
    return i;
}

int findElement(int* &arr, int n, int k)
{
    int start = 0, end = n - 1;
    int p = -1;
    
    while( p != k ) {
        
        p = partition(arr, start, end);

        if( p < k )
            start = p + 1;
        if ( p > k )
            end = p - 1;
    }
    
    return arr[k];
}

int main() {
    
    int n, k;
    std::cin>>n>>k;
    
    int* arr = new int[n];
    
    
    for(int i = 0; i < n; i++) {
        std::cin>>arr[i];
    }
    
    
    int val = findElement(arr, n, k);
    std::cout<<val;
    
    delete [] arr;
    
    return 0;
}
