#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w(1050, 750);
    w.show();
    
    return a.exec();
}
