#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w(1000, 700);
    w.show();
    
    return a.exec();
}
