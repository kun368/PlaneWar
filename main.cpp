#include "myview.h"
#include <QMainWindow>
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyView view;
    QObject::connect(&view, SIGNAL(exitApp()), &a, SLOT(quit()));
    view.show();

    return a.exec();
}
