#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "evaluate.h"

using namespace std;

template <typename K,typename V>
class basehashTable
{
private:
    struct item
    {
        K key;
        V value;
        item* next;

        item() : key(nullptr), value(nullptr), next(nullptr) {}
        item(K k, V v,size_t size) : key(k), value(v), next(nullptr),tableSize(size) {}
    };
    const int tableSize;  // 存储量可改变
    item** HashTable;

    int size;


public:
    virtual int hashFunction(K str);//哈希函数
    virtual void PrintTable();
    virtual void PrintItemsInIndex(int index);

    basehashTable() {

        HashTable = new item * [tableSize];
        for (int i = 0; i < tableSize; ++i)
            HashTable[i] = new item();
        state = -1;
        size = 0;

    }
    ~basehashTable();
    void AddItem(K str, V vv) {
        int index = hashFunction(str);

        if (keyEmpty(HashTable[index]->key))
        {
            HashTable[index]->key = str;
            HashTable[index]->value = vv;
            size++;
        }
        else
        {
            item* p = HashTable[index];
            item* n = new item(str, vv);
            bool exist = false;
            while (p->next != nullptr && !(exist = !keyEqual(p->key, str)))
            {
                p = p->next;
            }
            if (exist)
                return;

            size++;
            p->next = n;
        }
    }
    int NumberOfItemsInIndex(int index)
    {
        int count = 0;
        if (keyEmpty( HashTable[index]->key))
        {
            return count;
        }
        else
        {
            count++;
            item* p = HashTable[index];
            while (p->next != nullptr)
            {
                count++;
                p = p->next;
            }
        }
        return count;
    }

    V find(K str)
    {
        int index = hashFunction(str);
        bool FindName = false;

        V v = nullptr;
        item* p = HashTable[index];

        state = -1;
        while (p != nullptr)
        {
            state++;
            if (!keyEmpty( p->key) && !strcmp(p->key, str))
            {
                FindName = true;
                v = p->value;
                break;
            }
            p = p->next;
        }
        if (!FindName)
            state = -1;

        return v;
    }
    void remove(K str)
    {
        int index = hashFunction(str);

        item* delPtr;
        item* p1;
        item* p2;

        // case0: bucket is empty
        if (keyEmpty( HashTable[index]->key) )
        {
            return;
        }
        // case1: only one item contained in the bucket, and that item has matching name
        else if (keyEmpty(HashTable[index]->key, str) == 0 && HashTable[index]->next == nullptr)
        {
            HashTable[index]->key = nullptr;
            size--;
        }
        // case 2: match is located in the first item in the bucket and there are more items in the bucket
        else if (keyEqual(HashTable[index]->key, str) == 0)
        {
            delPtr = HashTable[index];
            HashTable[index] = HashTable[index]->next;
            delete delPtr;
            size--;
        }
        // case 3: the bucket contains items, but first item is not a match
        else
        {
            p1 = HashTable[index]->next;
            p2 = HashTable[index];
            while (p1 != nullptr && keyEqual(p1->key, str))
            {
                p2 = p1;
                p1 = p1->next;
            }
            // case 3.1: no match
            if (p1 == nullptr)
            {
                return;
            }
            //case 3.2: match is found
            else
            {
                delPtr = p1;
                p1 = p1->next;
                p2->next = p1;
                delete delPtr;
                size--;
            }
        }
    }


    inline int getsize() { return size; }
    inline int getstate() { return state; }


protected:
    int state;//状态值，-1为找空，>=为链表的索引值
    virtual int keyEqual(const K& k1, const K& k2);
    virtual bool keyEmpty(const K& k);
    virtual bool valueEmpty(const V& v);
    virtual V valueNull();
    virtual K keyNull();

};







class hashTable:basehashTable<char*,int**>
{
private:
    struct item
    {
        char* key;
        int** value;
        item* next;

        item() : key(nullptr), value(nullptr), next(nullptr) {}
        item(char* k, int** v) : key(k), value(v), next(nullptr) {}
    };
    static const int tableSize = 100000;  // 存储量可改变
    item** HashTable;
    int state;//状态值，-1为找空，>=为链表的索引值
    int size;

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