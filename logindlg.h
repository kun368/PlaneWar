#ifndef LOGINDLG_H
#define LOGINDLG_H

#include "constants.h"
#include <QDialog>
#include <QComboBox>

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
    void on_pushButton_help_clicked();
    void on_pushButton_About_clicked();
private:
    void saveBackGroundType();
    void saveBackGroundLoop();
    Ui::LogInDlg *ui;
};

#endif // LOGINDLG_H
