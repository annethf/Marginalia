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
    }
    return temp;
}

int MainWindow::operate(int a, char b, int c)
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
    bool flag = false;
    QList<char>::Iterator iter = expList.begin();
    c = *iter;
    sOperator.push('#');
    while(c != '#' || sOperator.top() != '#')
    {
        if(!isOperator(c))
        {
            if(flag)
            {
                int tmp = sOperand.top();
                sOperand.pop();
                int num = tmp * 10 + c - '0';
                sOperand.push(num);
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
            switch(symbol){
            case '<':
                sOperator.push(c);
                c = *(++iter);
                flag = false;
                break;
            case '=':
                sOperator.pop();
                c = *(++iter);
                flag = false;
                break;
            case '>':
                theta = sOperator.pop();
                a =  sOperand.pop();
                b = sOperand.pop();
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

void MainWindow::on_zero_clicked()
{
    if(!expList.empty() && isOperator(expList.last()))
    {
        ui->lineEdit->clear();
        exp.clear();
        ui->lineEdit->setText("0");
    }
    else if(expList.empty());
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

void MainWindow::on_plus_clicked()
{
    expList.push_back('+');
}

void MainWindow::on_subduct_clicked()
{
    expList.push_back('-');
}

void MainWindow::on_equalButton_clicked()
{
    expList.push_back('#');
    result = calculate();
    if(result != -1)
    {
        exp = QString::number(result);
        ui->lineEdit->setText(exp);
    }
}

