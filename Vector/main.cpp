#include <iostream>
#include <fstream>
#include "Vector.h"

using namespace std;

int main()
{
    Vector<int> a;
    Vector<int> b;
    ifstream in("input.txt");
    ofstream out("output.txt");
    int number;
    while(in >> number)
    {
         a.pushBack(number);
         out << number << " ";
    }
    //Back()const
    cout << "[ Back = " << a.Back() << " ]" << endl;
    //Iterator
    for(Vector<int>::Iterator itr = a.Begin(); itr != a.End(); ++itr)
        cout << *itr << " ";
    cout << endl;
    //operator=
    b = a;
    //¿½±´¹¹Ôìº¯Êý
    Vector<int> c = b;
    //operator[]
    for(int i = 0; i < b.Size(); i++)
        cout << b[i] << " ";
    cout << endl;
    in.close();
    out.close();
    return 0;
}
