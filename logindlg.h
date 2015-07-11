#ifndef LOGINDLG_H
#define LOGINDLG_H

#include "constants.h"
#include <QDialog>
#include <QComboBox>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QBitmap>

namespace Ui {
class LogInDlg;
}

class LogInDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDlg(QWidget *parent = 0);
    ~LogInDlg();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_loadStart_clicked();
    void on_pushButton_help_clicked();
    void on_pushButton_About_clicked();
private:
    void saveBackGroundType();
    void saveBackGroundLoop();
    QPoint dragPosition;
    Ui::LogInDlg *ui;
};

#endif // LOGINDLG_H
