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
    for(int i = 0; i < a.Size(); i++)
        cout << a[i] << " ";
    cout << endl;
    b = a;
    for(int i = 0; i < b.Size(); i++)
        cout << b[i] << " ";
    cout << endl;
    in.close();
    out.close();
    return 0;
}
