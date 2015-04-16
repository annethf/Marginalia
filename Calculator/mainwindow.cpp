#include "mainwindow.h"
#include "ui_mainwindow.h"

const double MainWindow::INFINITE = 999999999;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    result = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isOperator(const char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
        return true;
    return false;
}

bool MainWindow::isPoint(const char c)
{
    return (c == '.') ? true : false;
}

//中缀表达式求值的算符优先关系
char MainWindow::precede(char a, char b)
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
        try
    {
        if(b == '#')
            throw "expression error!";
        if(b == '+' || b == '-' || b == '*' || b == '/' || b == '(')
            temp = '<';
        if(b == ')')
            temp = '=';
    }
        catch(const char* str)
        {
            cout << str << endl;
            temp = '!';
        }
        break;
    case ')':
        try
    {
        if(b == '(')
            throw "expression error!";
        if(b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '#')
            temp = '>';
    }
        catch(const char* str)
        {
            cout << str << endl;
            temp = '!';
        }
        break;
    case '#':
        try
    {
        if(b == ')')
            throw "expression error!";
        if(b == '+' || b == '-' || b == '*' || b == '/' || b == '(')
            temp = '<';
        if(b == '#')
            temp = '=';
    }
        catch(const char* str)
        {
            cout << str << endl;
            temp = '!';
        }
        break;
    }
    return temp;
}

double MainWindow::operate(double a, char b, double c)
{
    double num3 = INFINITE;
    switch(b){
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
            throw "The divisor is 0.";
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

double MainWindow::calculate()
{
    QStack<char> sOperator;
    QStack<double> sOperand;
    char c, theta;
    double a, b, temp, num, tmp;
    bool fLongInteger = false;
    bool fDecimal = false;
    int pCounter = 0;
    QList<char>::Iterator iter = expList.begin();
    c = *iter;
    sOperator.push('#');
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
            case '!':
                return INFINITE;
            }
        }
    }
    double value;
    try
    {
        if(sOperand.size() != 1)
            throw "Expression error!";
        value = sOperand.top();
    }
    catch(const char* str)
    {
        cout << str << endl;
        value =  INFINITE;
    }
    return value;
}

void MainWindow::on_zero_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();

        exp += "0";
        ui->lineEdit->setText("0");
    }
    else
    {
        exp += "0";
        ui->lineEdit->setText(exp);
    }
    expList.push_back('0');
}

void MainWindow::on_one_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();

        exp += "1";
        ui->lineEdit->setText("1");
    }
    else
    {
        exp += "1";
        ui->lineEdit->setText(exp);
    }
    expList.push_back('1');
}

void MainWindow::on_two_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();

        exp += "2";
        ui->lineEdit->setText("2");
    }
    else
    {
        exp += "2";
        ui->lineEdit->setText(exp);
    }
    expList.push_back('2');
}

void MainWindow::on_three_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();

        exp += "3";
        ui->lineEdit->setText("3");
    }
    else
    {
        exp += "3";
        ui->lineEdit->setText(exp);
    }
    expList.push_back('3');
}

void MainWindow::on_four_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();

        exp += "4";
        ui->lineEdit->setText("4");
    }
    else
    {
        exp += "4";
        ui->lineEdit->setText(exp);
    }
    expList.push_back('4');
}

void MainWindow::on_five_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();

        exp += "5";
        ui->lineEdit->setText("5");
    }
    else
    {
        exp += "5";
        ui->lineEdit->setText(exp);
    }
    expList.push_back('5');
}

void MainWindow::on_six_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();

        exp += "6";
        ui->lineEdit->setText("6");
    }
    else
    {
        exp += "6";
        ui->lineEdit->setText(exp);
    }
    expList.push_back('6');
}

void MainWindow::on_seven_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();

        exp += "7";
        ui->lineEdit->setText("7");
    }
    else
    {
        exp += "7";
        ui->lineEdit->setText(exp);
    }
    expList.push_back('7');
}

void MainWindow::on_eight_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();

        exp += "8";
        ui->lineEdit->setText("8");
    }
    else
    {
        exp += "8";
        ui->lineEdit->setText(exp);
    }
    expList.push_back('8');
}

void MainWindow::on_nine_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();

        exp += "9";
        ui->lineEdit->setText("9");
    }
    else
    {
        exp += "9";
        ui->lineEdit->setText(exp);
    }
    expList.push_back('9');
}

void MainWindow::on_point_clicked()
{
    if(!expList.empty())
    {
        if(isOperator(expList.last()))
        {
            ui->lineEdit->clear();
            exp.clear();

            exp += "0.";
            expList.push_back('0');
            expList.push_back('.');
            ui->lineEdit->setText(exp);
        }
        else
        {
            exp += ".";
            expList.push_back('.');
            ui->lineEdit->setText(exp);
        }
    }
    else
    {
        exp += "0.";
        expList.push_back('0');
        expList.push_back('.');
        ui->lineEdit->setText(exp);
    }
}

void MainWindow::on_plus_clicked()
{
    if(expList.empty())
        expList.push_back('0');
    expList.push_back('+');
}

void MainWindow::on_subduct_clicked()
{
    if(expList.empty())
        expList.push_back('0');
    expList.push_back('-');
}


void MainWindow::on_multiplication_clicked()
{
    if(expList.empty())
        expList.push_back('0');
    expList.push_back('*');
}

void MainWindow::on_devision_clicked()
{
    if(expList.empty())
        expList.push_back('0');
    expList.push_back('/');
}

void MainWindow::on_leftBraket_clicked()
{
    expList.push_back('(');
}

void MainWindow::on_rightBracket_clicked()
{
    if(expList.last() == '(')
        expList.push_back('0');
    expList.push_back(')');
}

void MainWindow::on_equalButton_clicked()
{
    if(!expList.empty())
    {
        expList.push_back('#');
        result = calculate();
        exp = QString::number(result);
        ui->lineEdit->setText(exp);
        expList.clear();
        for(int i = 0; i < exp.size(); ++i)
            expList.push_back(exp.at(i).toLatin1()); //exp.at(i)是Qchar类型的一个对象，通过toLatin1()
        //或toAscii()转换成char基本类型
        //toAscii()和toLatin1()是Qchar类的成员函数
    }
    else
        ui->lineEdit->setText("0");
}

void MainWindow::on_clear_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit->setText("0");
    expList.clear();
    exp.clear();
}
