#include "hashTable.h"














int hashTable::hashFunction(char* str)
{
    int len = strlen(str);
    int index = 0;
    int mul = 1;
    for (int i = len - 1;i >= 0;i--) {
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

int hashTable::hashFunction(char* str,int len)
{
    int index = 0;
    int mul = 1;
    for (int i = len - 1;i >= 0;i--) {
        index += mul * (str[i] == '0' ? 1 : (str[i] == '1' ? 2 : 3));


        mul *= 3;
    }
    index = index % tableSize;

    return index;
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
    if (p->key == 0)
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

int* hashTable::find(char* str)
{
    int index = hashFunction(str);
    bool FindName = false;

    int* v = valueNull();
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


DoubleShape hashTable::getShape(char* str,int in)
{
    //字符串裁剪
    int tt = clock();

    int s = in-1;
    int e = 1;
    char* p = str+in-1;
    for (int d = -1;d >= -5 && *p != '/' && s >= 0;d--, p--, s--);
    p = str+in+1;
    for (;e <= 5 && *p != '/' && p;e++, p++);
    int s1 = s + 1;
    int e1 = in + e - 1;
   

    s = in - 1;
    e = 1;
    p = str + in - 1;
    for (int d = -1;d >= -5 && *p != '1' && s >= 0;d--, p--, s--);
    p = str + in + 1;
    for (;e <= 5 && *p != '1' && p;e++, p++);
    int s2 = s + 1;
    int e2 = in + e - 1;



    char* str1 = new char[12]{ 0 };
    memcpy(str1, str + s1, (e1 - s1 + 1) * sizeof(char));
    char* str2 = new char[12]{ 0 };
    memcpy(str2, str + s2, (e2 - s2 + 1) * sizeof(char));


    int* ans1 = new int[8]{ 0 };
    int* ans2 = new int[8]{ 0 };
    DoubleShape ans(ans1, ans2);
/*
    int* ans1 = find(str1);
    int* ans2 = find(str2);
    DoubleShape ans(ans1, ans2);
    
    
    if (ans1&&ans2) {
        if (ans1[3])
            int aa = 1;
        delete str1;
        delete str2;

        return ans;
    }
    */
    timetemp += clock() - tt;



    //未查到
    int* v = new int[SHAPE_TYPES]{ 0 };
    if (ans1) {

        tree1->get(str + s1, e1 - s1 + 1, v);
        AddItem(str1, v);
    }
    else delete str1;
    int* _v = new int[SHAPE_TYPES]{ 0 };
    if (ans2) {

        tree2->get(str + s2, e2 - s2 + 1, _v);
        AddItem(str2, _v);
    }
    else delete str2;
    ans[0] = v;
    ans[1] = _v;
    state = -1;

    if (ans[0][3] != 0) {
        int aa = 1;
    }



    return ans;
}



void hashTable::init()
{
    //生成10位长的棋盘
    for (int length = 1; length <= 12; ++length) {
        generateStrings("", 0, length, 1);
    }
    return;
}



void hashTable::generateStrings(string current, int len, int maxLength, int samecount) {
    // 如果当前字符串的长度达到了最大长度
    if (len == maxLength) {
        //末尾超过3个'0'
        if (maxLength > 3 && current[len - 1] == '0' && current[len - 2] == '0' && current[len - 3] == '0' && current[len - 4] == '0') return;


        int* v = new int[7]{ 0 };
        int* _v = new int[7]{ 0 };
        int** vv = new int* [2]{ v,_v };
        tree1->get(current.c_str(), len, v);
        tree2->get(current.c_str(), len,_v);


        char* nstr = new char[maxLength + 1]{ 0 };
        strcpy(nstr, current.c_str());
        //AddItem(nstr, vv);


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
TransitionTable TT;





