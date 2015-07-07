#include "logindlg.h"
#include "ui_logindlg.h"

LogInDlg::LogInDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDlg)
{
    ui->setupUi(this);
    connect(ui->pushButton_exit, SIGNAL(clicked(bool)), this, SLOT(close()));
}

LogInDlg::~LogInDlg()
{
    delete ui;
}

void LogInDlg::on_pushButton_start_clicked()
{
    accept();
}
