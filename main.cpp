#include "myview.h"
#include <QMainWindow>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyView view;
    view.show();

    return a.exec();
}
