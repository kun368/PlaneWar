#include "logindlg.h"
#include "ui_logindlg.h"
#include <QIcon>
#include <QTextEdit>
#include <QPalette>

LogInDlg::LogInDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDlg)
{
    ui->setupUi(this);
    connect(ui->pushButton_exit, SIGNAL(clicked(bool)), this, SLOT(close()));
    QIcon icon(":/images/Icon.png");
    setWindowIcon(icon);
    setWindowOpacity(0.9);
    setFixedSize(width(), height());

    QPalette pl = ui->textEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    ui->textEdit->setPalette(pl);
}

LogInDlg::~LogInDlg()
{
    delete ui;
}

void LogInDlg::on_pushButton_start_clicked()
{
    loadmode = false;
    accept();
}

void LogInDlg::on_pushButton_loadStart_clicked()
{
    loadmode = true;
    accept();
}
