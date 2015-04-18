#include "widget.h"
#include "ui_widget.h"

Widget::Widget(int h, int w, QWidget *parent) :
    height(h), width(w), QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置窗口大小
    this->setFixedSize(h, w);
    //用调色板设置窗口背景颜色
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255, 255, 255));
    this->setPalette(palette);

    flag = false;
    connect(ui->createButton, SIGNAL(clicked()), SLOT(draw()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    for(int i = 0; i < 49; ++i)
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
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::black, Qt::Dense5Pattern));

    //迷宫初始状态
    int xc = 0, yc = 50;
    int text = 1;
    QFont font;
    for(int i = 1; i <= 7; ++i)
    {
        xc = 0;
        for(int j = 1; j <= 8; ++j)
        {
            painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
            painter.drawRect(xc, yc, 50, 50);
            font.setPixelSize(30);
            painter.setFont(font);
            painter.setPen(Qt::red);
            if(j <= 7)
            {
                QRect rect(xc + 50, yc + 5, 50, 50);
                painter.drawText(rect, Qt::AlignHCenter, QString::number(text));
                text++;
            }
            xc += 100;
        }
        yc += 100;
    }
    yc = 0;
    for(int i = 1; i <= 8; ++i)
    {
        xc = 0;
        for(int j = 1; j <= 15; ++j)
        {
            painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
            painter.drawRect(xc, yc, 50, 50);
            xc += 50;
        }
        yc += 100;
    }
}
