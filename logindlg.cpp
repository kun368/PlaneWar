#include "logindlg.h"
#include "ui_logindlg.h"
#include <QIcon>

LogInDlg::LogInDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDlg)
{
    ui->setupUi(this);
    connect(ui->pushButton_exit, SIGNAL(clicked(bool)), this, SLOT(close()));
    QIcon icon(":/images/Icon.png");
    setWindowIcon(icon);
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
