#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QPushButton>
#include <QtGlobal>
#include <QStack>
#include "time.h"
#include <iostream>

using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(int h, int w, QWidget *parent = 0);
    ~Widget();

    void init();
    int find(int x);
    void unionSet(int x, int y);
    int pos(int x, int y);
    bool createMaze();
    bool pass(QPoint curPos);
    void footPrint(QPoint curPos);
    QPoint nextPos(QPoint curPos, int direct);
    void markPrint(QPoint point);
//    bool mazePath();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void drawMaze();

private:
    Ui::Widget *ui;
    const int width;
    const int height;
    int parent[170];
    int mazeSet[15][15];
    QPushButton createButton;
    bool dflag;
};

class MazePathElem
{
public:
    explicit MazePathElem();
    friend class Widget;
private:
    QPoint seat;
    int direct;
    int order;
};

#endif // WIDGET_H
