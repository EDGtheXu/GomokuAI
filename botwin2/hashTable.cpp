#include "hashTable.h"
















hashTable::hashTable()
{
    HashTable = new item * [tableSize];
    for (int i = 0; i < tableSize; ++i)
        HashTable[i] = new item();
    state = -1;
    size = 0;
}

hashTable::~hashTable()
{

}

int hashTable::hashFunction(char* str)
{
    int len = strlen(str);
    /*
    for (size_t i = 0; i < len; ++i)
    {
        sum += static_cast<int>(str[i]);
    }*/
    int index = 0;
    int mul = 1;
    for (int i = len-1;i >= 0;i--) {
        index += mul * (str[i] == '0' ? 1 : (str[i] == '1' ? 2 : 3));


        mul *= 3;
    }
    index = index % tableSize;

    /*
    cout << "key[0] = " << key[0] << endl;
    cout << "key[0] = " << static_cast<int>(key[0]) << endl;
    cout << "key[1] = " << key[1] << endl;
    cout << "key[2] = " << key[2] << endl;
    cout << "sum = " << sum << endl;
    cout << "index = " << index << endl << endl;
    */
    return index;
}

void hashTable::AddItem(char* str, int** vv)
{
    int index = hashFunction(str);

    if (HashTable[index]->key == nullptr)
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
        while (p->next != nullptr && !(exist=!strcmp(p->key,str)))
        {
            p = p->next;
        }
        if (exist) 
            return;

        size++;
        p->next = n;
    }
}

int hashTable::NumberOfItemsInIndex(int index)
{
    int count = 0;
    if (HashTable[index]->key == nullptr)
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

void hashTable::PrintTable()
{
    int number;
    for (int i = 0; i < tableSize; ++i)
    {
        number = NumberOfItemsInIndex(i);
        cout << "index = " << i << ": " << endl;
        cout << "key = " << HashTable[i]->key << endl;
        cout << "value = " << HashTable[i]->value << endl;
        cout << "冲突次数 = " << number << endl << endl;
    }
}

void hashTable::PrintItemsInIndex(int index)
{
    item* p = HashTable[index];
    if (p->key == nullptr)
    {
        cout << "index = " << index << "is empty";
    }
    else
    {
        cout << "index " << index << " contains the following items \n";
        while (p != nullptr)
        {
            cout << p->key << ", " << p->value << endl;
            p = p->next;
        }
    }
}

int** hashTable::find(char* str)
{
    int index = hashFunction(str);
    bool FindName = false;

    int** v = nullptr;
    item* p = HashTable[index];

    state = -1;
    while (p != nullptr)
    {
        state++;
        if (p->key&&!strcmp( p->key , str))
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

void hashTable::remove(char* str)
{
    int index = hashFunction(str);

    item* delPtr;
    item* p1;
    item* p2;

    // case0: bucket is empty
    if (HashTable[index]->key == nullptr)
    {
        return;
    }
    // case1: only one item contained in the bucket, and that item has matching name
    else if (strcmp( HashTable[index]->key, str)==0 && HashTable[index]->next == nullptr)
    {
        HashTable[index]->key = nullptr;
        size--;
    }
    // case 2: match is located in the first item in the bucket and there are more items in the bucket
    else if (strcmp(HashTable[index]->key, str) == 0)
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
        while (p1 != nullptr && strcmp( p1->key , str))
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


int** hashTable::getShape(char* str)
{
    int** ans = find(str);
    if (ans) return ans;


    //未查到
    int* v = new int[7]{ 0 };
    int* _v = new int[7]{ 0 };
    int** vv = new int* [2]{ v,_v };
    tree1->get(str, v);
    tree2->get(str, _v);

    AddItem(str, vv);
    state = -1;
    return vv;
}



void hashTable::init()
{
    //生成10位长的棋盘
    for (int length = 1; length <= 10; ++length) {
        generateStrings("", 0, length, 1);
    }

}



void hashTable::generateStrings(string current, int len, int maxLength, int samecount) {
    // 如果当前字符串的长度达到了最大长度
    if (len == maxLength) {
        //末尾超过3个'0'
        if (maxLength > 3 && current[len - 1] == '0' && current[len - 2] == '0' && current[len - 3] == '0' && current[len - 4] == '0') return;


        int* v = new int[7]{ 0 };
        int* _v = new int[7]{ 0 };
        int** vv = new int* [2]{ v,_v };
        tree1->get(current.c_str(), v);
        tree2->get(current.c_str(), _v);


        char* nstr = new char[maxLength + 1]{ 0 };
        strcpy(nstr, current.c_str());
        AddItem(nstr, vv);


        return;
    }
    // 遍历所有可能的字符  
    for (char c : {'0', '1', '/'}) {
        // 递归调用，向当前字符串添加一个字符，并尝试达到最大长度  

        if (len == 3 && c == '0' && current[0] == '0' && current[1] == '0' && current[2] == '0')
            continue;//前面空白保留3位'0'

        bool ifsame = (len == 0 ? false : current[len - 1] == c);
        if (samecount > 4 && ifsame && c != '0') {
            //cout<<current<<endl;
            continue;//已经连5
        }
        generateStrings(current + c, len + 1, maxLength, ifsame ? samecount + 1 : 1);
    }
}


hashTable shapeHashTable;