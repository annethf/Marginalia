#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isOperand(char c)
{
    if(c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')')
        return true;
    return false;
}

bool isNotHigher(char c, char e)
{
    char temp;
    switch(c)
    {
    case '+':
    case '-':
        if(e == ')')
            temp = '>';
        if(e == '+' || e == '-' || e == '*' || e == '/' || e == '(')
            temp = '<';
        break;
    case '*':
    case '/':
        if(e == '+' || e == '-' || e == ')')
            temp = '>';
        if(e == '*' || e == '/' || e == '(')
            temp = '<';
        break;
    case '(':
        if(e == '+' || e == '-' || e == '*' || e == '/' || e == '(')
            temp = '>';
        break;
    }
    return temp == '<' ? true : false;
}

string infix2postfix(string infix)
{
    stack<char> s;
    unsigned i = 0;
    char c, e;
    string postfix = "";
    while(i < infix.length() || !s.empty())
    {
        if(i < infix.length())
        {
            c = infix.at(i);
            if(isOperand(c))
            {
                postfix.push_back(c);
                i++;
            }
            else //������
            {
                while(!s.empty())
                {
                    e = s.top();
                    if(c == ')')
                    {
                        while(e != '(')
                        {
                            postfix.push_back(e);
                            s.pop();
                            e = s.top();
                        }
                        s.pop();
                        i++;
                        break;
                    }
                    else if(isNotHigher(c, e) && e != '(')
                    {
                        postfix.push_back(e);
                        s.pop();
                    }
                    else break;
                }
                if(c != ')')
                {
                    s.push(c);
                    i++;
                }
            }
        }
        else //infix��Ԫ��ȫ��ȡ�꣬��ջ������
        {
            while(!s.empty())
            {
                e = s.top();
                postfix.push_back(e);
                s.pop();
            }
        }
    }
    return postfix;
}

int main()
{
    //����ת������֮ǰ���뱣֤��׺���ʽ�ǺϷ��ı��ʽ
    string infix = "a+b*c+(d*e+f)*g";
    string postfix = infix2postfix(infix);
    cout << "postfix = " << postfix << endl;
    return 0;
}
