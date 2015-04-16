#include <iostream>
#include <list>
#include <stack>
#define INFINITE 65535

using namespace std;

bool isOperator(const char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
        return true;
    return false;
}

bool isPoint(const char c)
{
    return (c == '.') ? true : false;
}

//中缀表达式求值的算符优先关系
char precede(char a, char b)
{
    char temp;
    switch(a)
    {
    case '+':
    case '-':
        if(b == '+' || b == '-' || b == ')' || b == '#')
            temp = '>';
        if(b == '*' || b == '/' || b == '(')
            temp = '<';
        break;
    case '*':
    case '/':
        if(b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '#')
            temp = '>';
        if(b == '(')
            temp = '<';
        break;
    case '(':
        if(b == '+' || b == '-' || b == '*' || b == '/' || b == '(')
            temp = '<';
        if(b == ')')
            temp = '=';
        break;
    case ')':
        if(b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '#')
            temp = '>';
        break;
    case '#':
        if(b == '+' || b == '-' || b == '*' || b == '/' || b == '(')
            temp = '<';
        if(b == '#')
            temp = '=';
        break;
    }
    return temp;
}

double operate(double a, char b, double c)
{
    double num3 = INFINITE;
    switch(b)
    {
    case '+':
        num3 = a + c;
        break;
    case '-':
        num3 = a - c;
        break;
    case '*':
        num3 = a * c;
        break;
    case '/':
        try
        {
            if(c == 0)
                throw "除数为0了";
            num3 = a / c;
        }
        catch(const char* str)
        {
            cout << str << endl;
        }
        break;
    }
    return num3;
}

double calculate(double result, list<char> expList)
{
    stack<char> sOperator;
    stack<double> sOperand;
    char c, theta;
    double a, b, temp, num, tmp;
    bool fLongInteger = false;
    bool fDecimal = false;
    int pCounter = 0;
    sOperator.push('#');
    list<char>::iterator iter = expList.begin();
    c = *iter;
    while(c != '#' || sOperator.top() != '#')
    {
        if(!isOperator(c))
        {
            if(isPoint(c))
            {
                fDecimal = true;
                fLongInteger = false;
                c = *(++iter);
                continue;
            }
            else
            {
                if(fDecimal)
                {
                    tmp = sOperand.top();
                    sOperand.pop();
                    ++pCounter;
                    switch(pCounter)
                    {
                    case 1:
                        num = tmp + (double)(c - '0') / 10;
                        break;
                    case 2:
                        num = tmp + (double)(c - '0') / 100;
                        break;
                    case 3:
                        num = tmp + (double)(c - '0') / 1000;
                        break;
                    case 4:
                        num = tmp + (double)(c - '0') / 10000;
                        break;
                    case 5:
                        num = tmp + (double)(c - '0') / 100000;
                        break;
                    case 6:
                        num = tmp + (double)(c - '0') / 1000000;
                        break;
                    case 7:
                        num = tmp + (double)(c - '0') / 10000000;
                        break;
                    case 8:
                        num = tmp + (double)(c - '0') / 100000000;
                        break;
                    }
                    sOperand.push(num);
                    c = *(++iter);
                    continue;
                }
                if(fLongInteger)
                {
                    tmp = sOperand.top();
                    sOperand.pop();
                    num = tmp * 10 + c - '0';
                    sOperand.push(num);
                    c = *(++iter);
                    continue;
                }
                else
                {
                    sOperand.push(c - '0');
                    fLongInteger = true;
                    c = *(++iter);
                    continue;
                }
            }
        }
        else
        {
            char symbol = precede(sOperator.top(), c);
            switch(symbol)
            {
            case '<':
                sOperator.push(c);
                c = *(++iter);
                fLongInteger = false;
                fDecimal = false;
                pCounter = 0;
                break;
            case '=':
                sOperator.pop();
                c = *(++iter);
                fLongInteger = false;
                fDecimal = false;
                pCounter = 0;
                break;
            case '>':
                theta = sOperator.top();
                sOperator.pop();
                a = sOperand.top();
                sOperand.pop();
                b = sOperand.top();
                sOperand.pop();
                temp = operate(b, theta, a);
                sOperand.push(temp);
                break;
            }
        }
    }
    return sOperand.top();
}

int main()
{
    list<char> exp;
    char c;
    cin >> c;
    while(c != '#')
    {
        exp.push_back(c);
        cin >> c;
    }
    exp.push_back('#');
    list<char>::iterator iter = exp.begin();
    for(; iter != --exp.end(); ++iter)
    {
        if(isOperator(*iter))
            cout << " " << *iter << " ";
        else cout << *iter;
    }
    double result = 0.0;
    result = calculate(result, exp);
    cout << " = " << result << endl;
    return 0;
}
