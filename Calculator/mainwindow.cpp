#include "mainwindow.h"
#include "ui_mainwindow.h"

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
//中缀表达式求值的算符优先关系
char MainWindow::precede(char a, char b)
{
    char temp;
    switch(a){
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

char MainWindow::operate(int a, char b, int c)
{
    double num3 = 0;
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
        num3 = a / c;
        break;
    }
    return num3;
}

int MainWindow::calculate()
{
    QStack<char> sOperator;
    QStack<double> sOperand;
    char c, theta;
    double a, b, temp;
    int i = 0;

    sOperator.push('#');
    while(!sOperator.empty())
    {
        c = expList.takeAt(i);
        if(!isOperator(c))
        {
            sOperand.push(c - 48);
            ++i;
            continue;
        }
        else
        {
            switch(precede(sOperator.pop(), c)){
            case '<':
                sOperator.push(c);
                ++i;
                break;
            case '=':
                sOperator.pop();
                ++i;
                break;
            case '>':
                theta = sOperator.pop();
                a = sOperand.pop();
                b = sOperand.pop();
                temp = operate(a, theta, b);
                sOperand.push(temp);
                break;
            case '!':
                return -1;
            }
        }
    }
    return sOperand.front();
}

void MainWindow::on_one_clicked()
{
    exp = "1";
    expList.push_back('1');
    ui->lineEdit->setText(exp);
}

void MainWindow::on_two_clicked()
{
    exp = "2";
    expList.push_back('2');
    ui->lineEdit->setText(exp);
}

void MainWindow::on_plus_clicked()
{
    exp = "+";
    expList.push_back('+');
    ui->lineEdit->setText(exp);
}

void MainWindow::on_equalButton_clicked()
{
    result = calculate();
    if(result != -1)
    {
        exp = QString::number(result);
        ui->lineEdit->setText(exp);
    }
}
