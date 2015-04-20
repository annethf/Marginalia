#include <iostream>
#include <map>
#include <list>
#include <string>

using namespace std;

list<unsigned> decToBinary(unsigned dNumber, unsigned base)
{
    unsigned result = dNumber / base;
    unsigned remainder = dNumber - result * base;
    list<unsigned> bNumber;
    bNumber.push_front(remainder);
    while(result != 0)
    {
        dNumber = result;
        result = dNumber / base;
        remainder = dNumber - result * base;
        bNumber.push_front(remainder);
    }
    if(bNumber.size() < 8)
        for(int i = bNumber.size(); i < 8; i++)
            bNumber.push_front(0);
    return bNumber;
}

const map<char, list<unsigned> > asscii()
{
    map<char, list<unsigned> > assciiDic;
    char first = ' ';
    unsigned start = 32;
    list<unsigned> ls;
    map<char, list<unsigned> >::iterator iter = assciiDic.begin();
    for(int i = 0; i < 95; i++, first++, start++, iter++)
    {
        ls = decToBinary(start, 2);
        assciiDic.insert(iter, map<char, list<unsigned> >::value_type(first, ls));
    }
    return assciiDic;
}

int main()
{
    map<char, list<unsigned> > assciiDic = asscii();
    map<char, list<unsigned> >::iterator ite = assciiDic.begin();
    for(; ite != assciiDic.end(); ite++)
    {
        cout << ite->first << "   ";
        for(list<unsigned>::iterator it = (ite->second).begin(); it != (ite->second).end(); it++)
            cout << *it;
        cout << endl;
    }

    char ch[3] = {'a', 'b', 'c'};
    list< list<unsigned> > abc;
    list<unsigned> a1 = assciiDic[ch[0]];
    list<unsigned> b1 = assciiDic[ch[1]];
    list<unsigned> c1 = assciiDic[ch[2]];

    abc.push_back(a1);
    abc.push_back(b1);
    abc.push_back(c1);

    list<unsigned>::iterator iter = a1.begin();
    for(; iter != a1.end(); iter++)
        cout << *iter << " ";
    cout << endl;
    return 0;
}
