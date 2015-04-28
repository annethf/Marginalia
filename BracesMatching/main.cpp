#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

bool isLeftBrace(char c)
{
    if(c == '(' || c == '[' || c == '{')
        return true;
    return false;
}

bool isRightBrace(char c)
{
    if(c == ')' || c == ']' || c == '}')
        return true;
    return false;
}

bool isMatch(char e, char c)
{
    if((e == '(' && c == ')') || (e == '[' && c == ']') || (e == '{' && c == '}'))
        return true;
    return false;
}

int main()
{
    fstream in;
    in.open("input.txt");
    char c;
    stack<char> s;
    while(in >> c)
    {
        if(isLeftBrace(c))
            s.push(c);
        else if(isRightBrace(c))
        {
            if(s.empty())
            {
                cout << "error!" << endl;
                break;
            }
            else
            {
                char e = s.top();
                s.pop();
                if(!isMatch(e, c))
                {
                    cout << "braces don't match!" << endl;
                    break;
                }
            }
        }
        else
            break;
    }
    in.close();
    return 0;
}
