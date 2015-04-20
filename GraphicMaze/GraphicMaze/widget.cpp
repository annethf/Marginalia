#include "widget.h"
#include "ui_widget.h"

MazePathElem::MazePathElem()
{
    seat.setX(0);
    seat.setY(0);
    direct = 0;
    order = 0;
}

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

    dflag = false;
    connect(ui->createButton, SIGNAL(clicked()), SLOT(drawMaze()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    int i, j;
    //每个顶点的父节点设为-1
    for(int i = 1; i <= 169; ++i)
        parent[i] = -1;
    //顶点
    for(i = 1; i <= 13; ++i)
        for(j = 1; j <= 13; ++j)
            mazeSet[i][j] = 0;

    for(j = 0; j < 15; j++)
    {
        mazeSet[0][j] = 1;
        mazeSet[14][j] = 1;
    }

    for(i = 1; i <= 13; i++)
    {
        mazeSet[i][0] = 1;
        mazeSet[i][14] = 1;
    }

    for(i = 1; i <= 13; ++i)
    {
        if(i % 2 == 1)
        {
            //顶点与顶点之间的边
            for(j = 2; j <= 12; j += 2)
                mazeSet[i][j] = 1;
        }
        else
        {
            //墙与墙之间的衔接处
            for(j = 2; j <= 12; j += 2)
                mazeSet[i][j] = 2;
            //顶点与顶点之间的边
            for(j = 1; j <= 13; j += 2)
                mazeSet[i][j] = 1;
        }
    }
}

int Widget::find(int x)
{
    if(parent[x] < 0)
        return x;
    else
        return parent[x] = find(parent[x]);
}

void Widget::unionSet(int root1, int root2)
{
    if(parent[root1] < parent[root2])
        parent[root1] = root2;
    else
    {
        if(parent[root1] == parent[root2])
            parent[root1]--;
        parent[root2] = root1;
    }
}

int Widget::pos(int x, int y)
{
    return (x - 1) * 13 + y;
}

bool Widget::pass(QPoint curPos)
{
    if(mazeSet[curPos.rx()][curPos.ry()] == 0)
        return true;
    return false;
}

void Widget::footPrint(QPoint curPos)
{
    mazeSet[curPos.rx()][curPos.ry()] = 9;
}

QPoint Widget::nextPos(QPoint curPos, int di)
{
    QPoint next;
    if(di == 1)
    {
        next.setX(curPos.rx());
        next.setY(curPos.ry() + 1);
    }
    else if(di == 2)
    {
        next.setX(curPos.rx() + 1);
        next.setY(curPos.ry());
    }
    else if(di == 3)
    {
        next.setX(curPos.rx());
        next.setY(curPos.ry() - 1);
    }
    else
    {
        next.setX(curPos.rx() - 1);
        next.setY(curPos.ry());
    }
    return next;
}

void Widget::markPrint(QPoint point)
{
    mazeSet[point.rx()][point.ry()] = 8;
}

bool Widget::createMaze()
{
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
            painter.setBrush(QBrush(Qt::yellow, Qt::Dense5Pattern));
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
            painter.setBrush(QBrush(Qt::yellow, Qt::Dense5Pattern));
            painter.drawRect(xc, yc, 50, 50);
            xc += 50;
        }
        yc += 100;
    }

    //绘制迷宫
    int x, y, x1, y1, x2, y2;
    init();
    qsrand(time(0));
    painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    while(find(pos(1, 1)) != find(pos(13, 13)))
    {
        //随机生成一条边
        do
        {
            x = (qrand() % 13) + 1;
            y = (qrand() % 13) + 1;
        }while(mazeSet[x][y] != 1);
        int d = x % 2;
        if(d == 1)
        {
            x1 = x;
            y1 = y + 1;
            x2 = x;
            y2 = y - 1;
            if(find(pos(x1, y1)) != find(pos(x2, y2)))
            {
                mazeSet[x][y] = 0;
                //拆除顶点与顶点之间的墙
                painter.drawRect(y * 50, x * 50, 50, 50);
                unionSet(pos(x1, y1), pos(x2, y2));
            }
        }
        else
        {
            x1 = x + 1;
            y1 = y;
            x2 = x - 1;
            y2 = y;
            if(find(pos(x1, y1)) != find(pos(x2, y2)))
            {
                mazeSet[x][y] = 0;
                painter.drawRect(y * 50, x * 50, 50, 50);
                unionSet(pos(x1, y1), pos(x2, y2));
            }
        }
    }
    QStack<MazePathElem> stack;
    QPoint curPos;
    curPos.setX(1), curPos.setY(1);
    int curStep = 1;
    MazePathElem e;
    do{
        if(pass(curPos))
        {
            footPrint(curPos);
            painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap));
            painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
            painter.drawRect(curPos.ry() * 50, curPos.rx() * 50, 50, 50);
            e.direct = 1;
            e.order = curStep;
            e.seat = curPos;
            stack.push(e);
            if(curPos.rx() == 13 && curPos.ry() == 13)
                return true;
            curPos = nextPos(curPos, 1);
            curStep++;
        }
        else
        {
            if(!stack.empty ())
            {
                e = stack.pop();
                while(e.direct == 4 && !stack.empty())
                {
                    markPrint(e.seat);
                    painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap));
                    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
                    painter.drawRect(e.seat.ry() * 50, e.seat.rx() * 50, 50, 50);
                    e = stack.pop();
                }
                if(e.direct < 4)
                {
                    e.direct++;
                    stack.push(e);
                    curPos = nextPos(e.seat, e.direct);
                }
            }
        }
    }while(!stack.empty());
    return false;
}

void Widget::drawMaze()
{
    dflag = true;
    update();
}

void Widget::paintEvent(QPaintEvent *)
{
    if(!dflag)
        return;
    createMaze();
}
