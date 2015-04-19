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

void Widget::initRect()
{
    int i, j;
    //每个顶点的父节点设为-1
    for(i = 0; i < 169; ++i)
        parentRect[i] = -1;

    for(i = 0; i < 13; i++)
        for(j = 0; j < 13; j++)
            mazeRectSet[i][j] = 0;

    for(i = 0; i < 13; i++)
    {
        if(i % 2 == 0)
        {
            //顶点与顶点之间的边
            for(j = 1; j < 12; j += 2)
                mazeRectSet[i][j] = 1;
        }
        else
        {
            //墙与墙之间的衔接处
            for(j = 1; j < 12; j += 2)
                mazeRectSet[i][j] = 2;
            //顶点与顶点之间的边
            for(j = 0; j < 13; j += 2)
                mazeRectSet[i][j] = 1;
        }
    }

    cout << "60Maze" << endl;
    for(i = 0; i < 13; i++)
    {
        for(j = 0; j < 13; j++)
            cout << mazeRectSet[i][j] << " ";
        cout << endl;
    }
}

int Widget::find(int x)
{
    if(parentRect[x] < 0)
        return x;
    else
        return parentRect[x] = find(parentRect[x]);
}

void Widget::unionSet(int root1, int root2)
{
    if(parentRect[root1] < parentRect[root2])
        parentRect[root1] = root2;
    else
    {
        if(parentRect[root1] == parentRect[root2])
            parentRect[root1]--;
        parentRect[root2] = root1;
    }
}

int Widget::posRect(int x, int y)
{
    return x * 13 + y;
}

bool Widget::pass(QPoint curPos)
{
    if(mazeRectSet[curPos.rx()][curPos.ry()] == 0)
        return true;
    return false;
}

void Widget::footPrint(QPoint curPos)
{
    mazeRectSet[curPos.rx()][curPos.ry()] = 9;
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawRect((curPos.ry() + 1) * 50, (curPos.rx() + 1) * 50, 50, 50);
}

QPoint Widget::nextPos(QPoint curPos, int direct)
{
    QPoint next;
    if(direct == 1)
    {
        next.setX(curPos.rx());
        next.setY(curPos.ry() + 1);
    }
    else if(direct == 2)
    {
        next.setX(curPos.rx() + 1);
        next.setY(curPos.ry());
    }
    else if(direct == 3)
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
    mazeRectSet[point.rx()][point.ry()] = 8;
    QPainter painter(this);
    painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawRect((point.ry() + 1) * 50, (point.rx() + 1) * 50, 50, 50);
}

bool Widget::mazeRectPath()
{
    QStack<MazePathElem> stack;
    QPoint curPos;
    curPos.setX(0), curPos.setY(0);
    int curStep = 1;
    MazePathElem e;
    do{
        if(pass(curPos))
        {
            footPrint(curPos);
            e.direct = 1;
            e.order = curStep;
            e.seat = curPos;
            stack.push(e);
            if(curPos.rx() == 12 && curPos.ry() == 12)
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

void Widget::createRectMaze()
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
    initRect();
    qsrand(time(0));
    painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    while(find(posRect(0, 0)) != find(posRect(12, 12)))
    {
        //随机生成一条边
        do
        {
            x = qrand() % 13;
            y = qrand() % 13;
        }while(mazeRectSet[x][y] != 1);

        int d = x % 2;
        if(d == 0)
        {
            x1 = x;
            y1 = y + 1;
            x2 = x;
            y2 = y - 1;
            if(find(posRect(x1, y1)) != find(posRect(x2, y2)))
            {
                mazeRectSet[x][y] = 100;
                //拆除顶点与顶点之间的墙
                painter.drawRect((y + 1) * 50, (x + 1) * 50, 50, 50);
                unionSet(posRect(x1, y1), posRect(x2, y2));
            }
        }
        else
        {
            x1 = x + 1;
            y1 = y;
            x2 = x - 1;
            y2 = y;
            if(find(posRect(x1, y1)) != find(posRect(x2, y2)))
            {
                mazeRectSet[x][y] = 100;
                painter.drawRect((y + 1) * 50, (x + 1) * 50, 50, 50);
                unionSet(posRect(x1, y1), posRect(x2, y2));
            }
        }
    }
    mazeRectPath();
}

void Widget::drawMaze()
{
    dflag = true;
    repaint();
}

void Widget::paintEvent(QPaintEvent *)
{
    if(!dflag)
        return;
    createRectMaze();
}
