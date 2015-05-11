#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;

bool contains(vector<size_t> v, size_t index)
{
    if(std::find(v.begin(), v.end(), index) != v.end())
        return true;
    return false;
}

//生成的谜板是一个方阵
void createTable(char **table, int tSize, string str)
{
    vector<char> alphabet;
    vector<size_t> randomNum;
    size_t index = 0;

    srand(time(NULL));
    index = rand() % str.length();
    randomNum.push_back(index);
    for(size_t i = 0; i < str.length(); i++)
    {
        while(i > 0 && i < str.length())
        {
            index = rand() % str.length();
            if(!contains(randomNum, index))
            {
                randomNum.push_back(index);
                break;
            }
        }
        alphabet.push_back(str.at(index));
    }

    char c = 0;
    vector<char>::iterator iter = alphabet.begin();
    cout << tSize << endl;
    for(int i = 0; i < tSize; i++)
    {
        for(int j = 0; j < tSize; j++)
        {
            if(iter != alphabet.end())
            {
                table[i][j] = *iter;
                iter++;
            }
            else
            {
                c = 97 + rand() % 25;
                table[i][j] = c;
            }
        }
    }
    for(int i = 0; i < tSize; i++)
    {
        for(int j = 0; j < tSize; j++)
            cout << table[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    int tSize;
    cout << "请输入谜板大小:";
    cin >> tSize;
    char **table = new char*[tSize];
    for(int i = 0; i < tSize; i++)
        table[i] = new char[tSize];

    cout << "请输入单词表:";
    string str = "thistwofatthat";
    cin >> str;
    //生成随机谜板
    createTable(table, tSize, str);

    for(int i = 0; i < tSize; i++)
        delete [] table[i];
    delete [] table;

    return 0;
}
