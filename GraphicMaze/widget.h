#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QPushButton>
#include <QtGlobal>
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
    void createMaze();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void draw();

private:
    Ui::Widget *ui;
    const int width;
    const int height;
    int parent[49];
    //int mazeSet[14][14];
    QPushButton createButton;
    bool flag;

};

#endif // WIDGET_H
