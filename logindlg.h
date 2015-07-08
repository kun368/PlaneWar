#ifndef LOGINDLG_H
#define LOGINDLG_H

#include "constants.h"
#include <QDialog>

namespace Ui {
class LogInDlg;
}

class LogInDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDlg(QWidget *parent = 0);
    ~LogInDlg();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_loadStart_clicked();

private:
    Ui::LogInDlg *ui;
};

#endif // LOGINDLG_H
