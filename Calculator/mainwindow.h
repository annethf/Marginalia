#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include <QStack>

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
    int calculate();
    bool isOperator(const char c);
    char precede(char a, char b);
    int operate(int a, char b, int c);

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
    int result;
};

#endif // MAINWINDOW_H
