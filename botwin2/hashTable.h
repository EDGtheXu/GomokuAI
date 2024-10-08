#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "config.h"
#include "evaluate.h"

using namespace std;

template <typename K, typename V>
class basehashTable
{
protected:
    struct item
    {
        K key;
        V value;
        item* next;

        item(K k, V v) : key(k), value(v), next(nullptr) {}
    };
    const int tableSize;  // 存储量可改变
    item** HashTable;

    int size;


public:
    int hitCount = 0;
    int unHitCount = 0;
    //哈希公用方法
    inline basehashTable(int s) :tableSize(s) {

        HashTable = new item * [tableSize];
        for (int i = 0; i < tableSize; ++i)
            HashTable[i] = new item(keyNull(), valueNull());
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
            while (p->next != nullptr && !(exist = !keyCmp(p->key, str)))
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
        if (keyEmpty(HashTable[index]->key))
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
        else if (keyCmp(HashTable[index]->key, str) == 0)
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
            while (p1 != nullptr && keyCmp(p1->key, str))
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
            if (!keyEmpty(p->key) && !keyCmp(p->key, str))
            {
                FindName = true;
                v = p->value;
                break;
            }
            p = p->next;
        }
        if (!FindName) {
            state = -1;
            unHitCount++;
        }
        else {
            hitCount++;
        }


        return v;
    }
    inline int getsize() { return size; }
    inline int getstate() { return state; }
    virtual inline bool keyEmpty(K k) { return !keyCmp(k, keyNull()); }
    inline bool valueEmpty(V v) { return valueEqual(v, valueNull()); };
    virtual int hashFunction(K str) = 0;//哈希函数
//哈希可重写方法
protected:
    int state;//状态值，-1为找空，>=为链表的索引值


    virtual int keyCmp(K k1, K k2) { return k1 != k2; }
    virtual int valueEqual(V v1, V v2) { return v1 == v2; }
    virtual V valueNull() { return nullptr; }
    virtual K keyNull() { return K{}; }


};



class DoubleShape {
public:
    int* v;
    int* _v;

    DoubleShape(int* v1, int* v2) :v(v1), _v(v2) {}
    int*& operator[](int index) {
        return index == 0 ? v : _v;
    }
};



class hashTable :public basehashTable<char*, int**>
{
    //重写方法
public:

    inline hashTable() :basehashTable<char*, int**>(100000) {};
    inline ~hashTable() {};
    int hashFunction(char* str);
    int hashFunction(char* str, int len);


protected:

    inline bool keyEmpty(char* k) { return k == nullptr; }
    inline char* keyNull() { return nullptr; }
    int keyCmp(char* k1, char* k2) { return strcmp(k1, k2); }


    //独有方法
public:
    void PrintTable();
    void PrintItemsInIndex(int index);
    void init();
    int** getShape(char* str);
    void generateStrings(string current, int len, int maxLength, int samecount);
};


enum ValueType {
    value_type_unvalid,
    value_type_static,
    value_type_VCF, 
    value_type_ab, 

    value_type_score,
    value_type_db
};

//局面置换表
extern U64 zobristInitRandom;

class TTEntrace
{
public:
    TTEntrace(Pos* ps, int c, int v) :value(v),moveCount(c) {
        for (int i = 0;i < moveCount;i++) {
            moves[i] = ps[i];
        }
    };
    TTEntrace() :moveCount(0), value(0) {}
    ~TTEntrace();

    Pos moves[200];//所有可移动的点
    Pos bestMove;
    int values[200]{ 0 };//保存上次的估值

    int moveCount=0;
    int value;//动态估值
    int depth;//更新深度
    int valueType = value_type_unvalid;
    int step;
    int dbEval = 0;
    playerEnum dbWiner;
    playerEnum turn;

private:


};


class TransitionTable :public basehashTable<U64, TTEntrace*> {
    //重写方法
public:

    inline TransitionTable() :basehashTable<U64, TTEntrace*>(1000000) {};
    inline ~TransitionTable() {};

protected:
    inline int hashFunction(U64 zobristkey) {
        return zobristkey % tableSize;
    }
    inline U64 keyNull() { return zobristInitRandom; };


    //独有方法
public:


};





#endif // HASHTABLE_H