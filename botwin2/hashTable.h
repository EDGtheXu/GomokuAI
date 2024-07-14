#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "config.h"
#include "evaluate.h"

using namespace std;

template <typename K,typename V>
class basehashTable
{
protected:
    struct item
    {
        K key;
        V value;
        item* next;

        item(K k, V v) : key(k), value(v), next(nullptr){}
    };
    const int tableSize;  // 存储量可改变
    item** HashTable;

    int size;


public:

//哈希公用方法
    inline basehashTable(int s) :tableSize(s) {

        HashTable = new item * [tableSize];
        for (int i = 0; i < tableSize; ++i)
            HashTable[i] = new item(keyNull(),valueNull());
        state = -1;
        size = 0;

    }
    inline virtual ~basehashTable() {};
    inline void AddItem(K str, V vv) {
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
    inline void remove(K str)
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
    inline int NumberOfItemsInIndex(int index)
    {
        int count = 0;
        if (keyEmpty(HashTable[index]->key))
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
    inline V find(K str)
    {
        int index = hashFunction(str);
        bool FindName = false;

        V v = valueNull();
        item* p = HashTable[index];

        state = -1;
        while (p != nullptr)
        {
            state++;
            if (!keyEmpty( p->key) && !keyEqual(p->key, str))
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
    inline int getsize() { return size; }
    inline int getstate() { return state; }
    inline bool keyEmpty(K k) { return keyEqual(k, keyNull()); }
    inline bool valueEmpty(V v) { return valueEqual(v, valueNull()); };

//哈希可重写方法
protected:
    int state;//状态值，-1为找空，>=为链表的索引值

    virtual int hashFunction(K str) = 0;//哈希函数
    virtual int keyEqual(K k1, K k2){return k1 == k2;}
    virtual int valueEqual(V v1, V v2) { return v1 == v2; }
    virtual V valueNull() { return nullptr; }
    virtual K keyNull() {  return K{}; }


};







class hashTable:basehashTable<char*,int**>
{
//重写方法
public:
    
    inline hashTable() :basehashTable<char*, int**>(100000) {};
    inline ~hashTable() {};

protected:
    int hashFunction(char* str);
    inline int keyEqual(const char*& k1, const char*& k2) { return strcmp(k1, k2); }
    inline char* keyNull() { return nullptr; }

//独有方法
public:
    void PrintTable();
    void PrintItemsInIndex(int index);
    void init();
    int** getShape(char* str);
    void generateStrings(string current, int len, int maxLength, int samecount);
};




//局面置换表
extern U64 zobristInitRandom;
class TTEntrace
{
public:
    TTEntrace();
    ~TTEntrace();

    Pos moves[150];//所有可移动的点
    int value;//动态估值


private:


};


class TransitionTable :basehashTable<U64, TTEntrace*> {
    //重写方法
public:

    inline TransitionTable():basehashTable<U64, TTEntrace*>(1000000) {};
    inline ~TransitionTable() {};

protected:
    inline int hashFunction(U64 zobristkey) {
        return zobristkey % tableSize;
    }
    inline U64 keyNull() { return zobristInitRandom; };


    //独有方法


};





#endif // HASHTABLE_H