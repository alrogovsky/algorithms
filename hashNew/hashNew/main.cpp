//
//  main.cpp
//  hashTable
//
//  Created by Alexander Rogovsky on 30.04.15.
//  Copyright (c) 2015 Alexander Rogovsky. All rights reserved.
//

#define GROW_RATE 2
#define DELETED "!DEL"

#include <iostream>
#include <vector>

using namespace std;


const int HashParam = 37;
const int InitTableSize = 8;

int Hash(const std::string& data, size_t m){
    int hash = 0;
    
    for (size_t i = 0; i < data.length(); ++i) {
        hash = (hash * HashParam + data[i]) % m;
    }
    
    return hash;
}

int Probe(int hash, int probe, int m)
{
    return (hash + (probe * (probe + 1) / 2) ) % m;
}


template <class T>
class CHashTable {
public:
    CHashTable();
    
    bool Add( const T& data );
    bool Remove (const T& data);
    bool Has ( const T& data );
    
    void print(){
        for(size_t i = 0; i < table.size(); i++)
        {
            cout<<table[i]<<" | ";
        }
    }
private:
    vector<T> table;
    int size;
    
    void grow();
    
};

int main() {
    
    CHashTable<string> H;
    std::string data;
    char command;

    while (std::cin >> command >> data) {
        switch (command) {
            case '+':
                std::cout << (H.Add(data) ? "OK" : "FAIL") << "\n";
                break;
            case '-':
                std::cout << (H.Remove(data) ? "OK" : "FAIL") << "\n";
                break;
            case '?':
                std::cout << (H.Has(data) ? "OK" : "FAIL") << "\n";
                break;
            default:
                break;
        }
        
    }
    
    return 0;
}


template <class T>
CHashTable<T>::CHashTable() : size(0)
{
    table.resize(InitTableSize);
    
}

template <class T>
void CHashTable<T>::grow()
{
    vector<T> old = table;
    vector<T> newTable(table.size() * GROW_RATE);
    table = newTable;
    size = 0;
    for ( int i = 0; i < old.size(); ++i )
        if ( old[i] != DELETED && old[i] != "" )
            Add(old[i]);
}


template <class T>
bool CHashTable<T>::Add(const T& data)
{
    if (  4 * (size + 1) > 3 * table.size() )
        grow();
    
    int insertPlace = -1;
    int main_hash = Hash(data, table.size());
    
    for(size_t i = 0; i < table.size(); ++i)
    {
        int hash = Probe(main_hash, static_cast<int>(i), static_cast<int>(table.size()));
        if(table[hash] == data)
            return false;
        
        if(insertPlace == -1 && table[hash] == DELETED)
            insertPlace = hash;
        
        
        else if(table[hash] == "" && insertPlace == -1)
        {
            table[hash] = data;
            ++size;
            return true;
        }
    }
    
    if( insertPlace != -1 ) {
        table[insertPlace] = data;
        ++size;
        return true;
    }
    
    return false;
}

template <class T>
bool CHashTable<T>::Has(const T& data)
{
    int main_hash = Hash(data, table.size());

    for(size_t i = 0; i < table.size(); ++i)
    {
        int hash = Probe(main_hash, static_cast<int>(i), static_cast<int>(table.size()));
        if(table[hash] == data)
            return true;
    }
    
    return false;

}

template <class T>
bool CHashTable<T>::Remove (const T& data)
{
    int main_hash = Hash(data, table.size());
    
    for(size_t i = 0; i < table.size(); ++i)
    {
        int hash = Probe(main_hash, static_cast<int>(i), static_cast<int>(table.size()));
        if(table[hash] == data)
        {
            table[hash] = DELETED;
            --size;
            return true;
        }
        
    }
    
    return false;

}














