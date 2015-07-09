#include "logindlg.h"
#include "ui_logindlg.h"
#include "helpdlg.h"
#include <QIcon>
#include <QTextEdit>
#include <QPalette>
#include <QString>
#include <QDebug>
#include <QMessageBox>

LogInDlg::LogInDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDlg)
{
    ui->setupUi(this);
    connect(ui->pushButton_exit, SIGNAL(clicked(bool)), this, SLOT(close()));
    setFixedSize(width(), height());
    QPalette plt = this->palette();
    plt.setBrush(QPalette::Window, QBrush(QPixmap(":/images/LogInBackground.jpg")));
    this->setPalette(plt);
    this->setAutoFillBackground(true);
}

LogInDlg::~LogInDlg()
{
    delete ui;
}

void LogInDlg::on_pushButton_start_clicked()
{
    loadmode = false;
    saveBackGroundType();
    saveBackGroundLoop();
    accept();
}

void LogInDlg::on_pushButton_loadStart_clicked()
{
    loadmode = true;
    saveBackGroundType();
    saveBackGroundLoop();
    accept();
}

void LogInDlg::on_pushButton_help_clicked()
{
    HelpDlg *dlg = new HelpDlg(this);
    dlg->setModal(true);
    dlg->show();
}

void LogInDlg::on_pushButton_About_clicked()
{
    QMessageBox::about(this, tr("关于作者"), tr("山东科技大学信息学院\n软件工程张正锟\n网址:WWW.ZZKUN.COM"));
}

void LogInDlg::saveBackGroundType()
{
    QString str = ui->comboBox->currentText();
    if(str == tr("星际迷航")) backgroundName = tr(":/images/background.png");
    else if(str == tr("死亡峡谷")) backgroundName = tr(":/images/bg2.jpg");
    else if(str == tr("天空之城")) backgroundName = tr(":/images/bg3.jpg");
    else if(str == tr("死神沙漠")) backgroundName = tr(":/images/bg4.jpg");
}

void LogInDlg::saveBackGroundLoop()
{
     QString str = ui->comboBox_2->currentText();
     if(str == "开启") backgroundLoop = true;
     else backgroundLoop = false;
}
