#include "widget.h"
#include "ui_widget.h"

Widget::Widget(int h, int w, QWidget *parent) :
    height(h), width(w), QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(h, w);
    flag = false;
    connect(ui->createButton, SIGNAL(clicked()), SLOT(draw()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    for(int i = 0; i < height * width - 1; ++i)
        parent[i] = -1;
}

int Widget::find(int x)
{
    if(parent[x] < 0)
        return x;
    else
        return parent[x] = find(parent[x]);
}

void Widget::unionSet(int x, int y)
{
    if(parent[y] < parent[x])
        parent[x] = y;
    else
    {
        if(parent[x] == parent[y])
            return;
        parent[y] = x;
    }

}

void Widget::draw()
{
    flag = true;
    update();
}

void Widget::paintEvent(QPaintEvent *)
{
    if(!flag)
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));

    QPoint p1, p2, p3;
    p1.setX(0), p1.setY(0);
    p2.setX(0), p2.setY(50);
    p3.setX(50), p3.setY(0);
    QPoint tp1, tp2, tp3;
    for(int i = 0; i < 15; ++i)
    {
        tp1.setX(p1.rx()), tp1.setY(p1.ry());
        tp2.setX(p2.rx()), tp2.setY(p2.ry());
        tp3.setX(p3.rx()), tp3.setY(p3.ry());
        for(int j = 0; j < 15; ++j)
        {
            painter.drawLine(p1, p2);
            p1.setX(p1.rx() + 50);
            p2.setX(p2.rx() + 50);
        }
        p1.setX(tp1.rx()), p1.setY(tp1.ry());
        for(int j = 0; j < 14; ++j)
        {
            painter.drawLine(p1, p3);
            p1.setX(p1.rx() + 50);
            p3.setX(p3.rx() + 50);
        }
        p1.setX(tp1.rx()), p1.setY(tp1.ry());
        p2.setX(tp2.rx()), p2.setY(tp2.ry());
        p3.setX(tp3.rx()), p3.setY(tp3.ry());
        p1.setX(0), p1.setY(p1.ry() + 50);
        p2.setX(0), p2.setY(p2.ry() + 50);
        p3.setX(p3.rx()), p3.setY(p3.ry() + 50);
    }
    p1.setX(tp1.rx()), p1.setY(tp1.ry());
    p3.setX(tp3.rx()), p3.setY(tp3.ry());
    p1.setY(p1.ry() + 50);
    p3.setY(p3.ry() + 50);
    for(int j = 0; j < 14; ++j)
    {
        painter.drawLine(p1, p3);
        p1.setX(p1.rx() + 50);
        p3.setX(p3.rx() + 50);
    }
}
