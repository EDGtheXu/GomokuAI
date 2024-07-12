#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "evaluate.h"

using namespace std;

class hashTable
{
private:
    struct item
    {
        char* key;
        int** value;
        item* next;

        item() : key(nullptr), value(nullptr), next(nullptr) {}
        item(char*k, int** v) : key(k), value(v), next(nullptr) {}
    };
    static const int tableSize = 100000;  // 存储量可改变
    item** HashTable;
    int state;//状态值，-1为找空，>=为链表的索引值
    int size;
    hash<string> hash;

public:
    int hashFunction(char* str);
    hashTable();
    ~hashTable();
    void AddItem(char* str, int** vv);
    int NumberOfItemsInIndex(int index);
    void PrintTable();
    void PrintItemsInIndex(int index);
    int** find(char* str);
    void remove(char* str);
    void init();
    int** getShape(char* str);
    void generateStrings(string current, int len, int maxLength, int samecount);
    inline int getsize() { return size; }
    inline int getstate() { return state; }
};

extern hashTable shapeHashTable;


#endif // HASHTABLE_H