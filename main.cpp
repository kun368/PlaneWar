#include "myview.h"
#include "logindlg.h"
#include <QMainWindow>
#include <QApplication>
#include <QObject>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInDlg dlg;
    dlg.show();
    if(dlg.exec() == QDialog::Accepted) {
        MyView view;
        view.show();
        return a.exec();
    }
    return 0;
}
