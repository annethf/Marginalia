#include <iostream>
#include <list>
#include <stack>

using namespace std;

bool isOperator(const char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
        return true;
    return false;
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
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        temp = '!';
        break;
    }
    return temp;
}

char operate(double a, char b, double c)
{
    double num3 = 0;
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
        num3 = a / c;
        break;
    }
    return num3;
}

double calculate(int result, list<char> expList)
{
    stack<char> sOperator;
    stack<int> sOperand;
    char c, theta;
    int a, b, temp;
    bool flag = false;
    sOperator.push('#');
    list<char>::iterator iter = expList.begin();
    c = *iter;
    while(iter != expList.end())
    {
        if(!isOperator(c))
        {
            if(flag)
            {
                int tmp = sOperand.top();
                sOperand.pop();
                int num = tmp * 10 + c - '0';
                sOperand.push(num);
                flag = false;
            }
            else
            {
                sOperand.push(c - '0');
                flag = true;
            }
            c = *(++iter);
            continue;
        }
        else
        {
            char symbol = precede(sOperator.top(), c);
            switch(symbol)
            {
            case '<':
                sOperator.push(c);
                c = *(++iter);
                break;
            case '=':
                sOperator.pop();
                c = *(++iter);
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
            case '!':
                return -1;
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
