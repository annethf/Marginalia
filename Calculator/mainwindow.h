#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include <QStack>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    double calculate();
    bool isOperator(const char c);
    bool isPoint(const char c);
    char precede(char a, char b);
    double operate(double a, char b, double c);

private slots:
    void on_one_clicked();
    void on_two_clicked();
    void on_plus_clicked();
    void on_equalButton_clicked();
    void on_three_clicked();
    void on_four_clicked();
    void on_five_clicked();
    void on_six_clicked();
    void on_seven_clicked();
    void on_eight_clicked();
    void on_nine_clicked();
    void on_zero_clicked();
    void on_subduct_clicked();
    void on_point_clicked();

    void on_multiplication_clicked();

    void on_devision_clicked();

    void on_clear_clicked();

    void on_leftBraket_clicked();

    void on_rightBracket_clicked();

private:
    Ui::MainWindow *ui;

    QPushButton zero;
    QPushButton one;
    QPushButton two;
    QPushButton three;
    QPushButton plus;
    QPushButton equalButton;
    QLineEdit lineEdit;

    QString exp;
    QList<char> expList;
    double result;
    static const double INFINITE;
};

#endif // MAINWINDOW_H
