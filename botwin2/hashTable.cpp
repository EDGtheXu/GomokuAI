#include "hashTable.h"














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



int** hashTable::getShape(char* str)
{
    int** ans = find(str);
    if (ans) {

        return ans;
    }


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
TransitionTable TT;





