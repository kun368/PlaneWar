#include "helpdlg.h"
#include "ui_helpdlg.h"
#include <QPalette>

HelpDlg::HelpDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDlg)
{
    ui->setupUi(this);
    setWindowTitle(tr("飞机大战游戏说明"));
    QPalette pl = ui->textEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    ui->textEdit->setPalette(pl);
}

HelpDlg::~HelpDlg()
{
    delete ui;
}
